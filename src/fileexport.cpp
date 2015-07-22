/***************************************************************************
 * Copyright (C) 2015 by Pablo Daniel Pareja Obregon                       *
 *                                                                         *
 * This is free software; you can redistribute it and/or modify            *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 2, or (at your option)     *
 * any later version.                                                      *
 *                                                                         *
 * This software is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this package; see the file COPYING.  If not, write to        *
 * the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,   *
 * Boston, MA 02110-1301, USA.                                             *
 ***************************************************************************/

#include "fileexport.h"

#include "cgraphicsscene.h"
#include "component.h"
#include "idocument.h"
#include "portsymbol.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>

namespace Caneda
{
    //! \brief Constructor.
    FormatSpice::FormatSpice(SchematicDocument *doc) :
        m_schematicDocument(doc)
    {
    }

    bool FormatSpice::save()
    {
        CGraphicsScene *scene = cGraphicsScene();
        if(!scene) {
            return false;
        }

        QString text = saveText();

        if(text.isEmpty()) {
            qDebug("Looks buggy! Null data to save! Was this expected?");
        }

        QFile file(fileName());
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(0, QObject::tr("Error"),
                    QObject::tr("Cannot save document!"));
            return false;
        }

        QTextStream stream(&file);
        stream << text;
        file.close();

        return true;
    }

    SchematicDocument *FormatSpice::schematicDocument() const
    {
        return m_schematicDocument;
    }

    CGraphicsScene *FormatSpice::cGraphicsScene() const
    {
        return m_schematicDocument ? m_schematicDocument->cGraphicsScene() : 0;
    }

    QString FormatSpice::fileName() const
    {
        QString filename = QString();

        if(m_schematicDocument) {
            filename = m_schematicDocument->fileName() + ".net";
        }

        return filename;
    }

    QString FormatSpice::saveText()
    {
        QString retVal;

        //Fist we start the document and write the header
        retVal.append("* Spice automatic export. Generated by Caneda.\n");

        //Now we copy all the elements and properties in the schematic
        saveComponents(&retVal);
        savePorts(&retVal);
        saveWires(&retVal);

        return retVal;
    }

    void FormatSpice::saveComponents(QString *writer)
    {
        CGraphicsScene *scene = cGraphicsScene();
        QList<QGraphicsItem*> items = scene->items();
        QList<Component*> components = filterItems<Component>(items);
        if(!components.isEmpty()) {
            foreach(Component *c, components) {

                QString model = c->model("spice");
                QStringList modelBlocks = model.split(" ", QString::SkipEmptyParts);

                for(int i=0; i<modelBlocks.size(); i++){

                    QStringList modelSubBlocks = modelBlocks.at(i).split("%", QString::SkipEmptyParts);
                    for(int j=0; j<modelSubBlocks.size(); j++){

                        QStringList modelCommands = modelSubBlocks.at(j).split("=", QString::SkipEmptyParts);
                        if(modelCommands.at(0) == "label"){
                            writer->append(c->label());
                        }
                        else if(modelCommands.at(0) == "port"){
                            writer->append(modelCommands.at(1));
                        }
                        else if(modelCommands.at(0) == "property"){
                            writer->append(c->properties()->propertyValue(modelCommands.at(1)));
                        }
                        else{
                            writer->append(modelSubBlocks.at(j));
                        }

                    }
                    writer->append(" ");

                }
                writer->append("\n");
            }
        }
    }

    void FormatSpice::savePorts(QString *writer)
    {
        CGraphicsScene *scene = cGraphicsScene();
        QList<QGraphicsItem*> items = scene->items();
        QList<PortSymbol*> portSymbols = filterItems<PortSymbol>(items);
        if(!portSymbols.isEmpty()) {
            foreach(PortSymbol *p, portSymbols) {
                /*! \todo Here we must do some logic to group all nets with
                 *  the same port names into only one net number.
                 */
            }
        }
    }

    void FormatSpice::saveWires(QString *writer)
    {
        QList<QGraphicsItem*> items = cGraphicsScene()->items();
        QList<Wire*> wires = filterItems<Wire>(items);

        if(wires.isEmpty()) {
            return;
        }

        int wireId = 0;
        int equiId = 0;
        QList<Wire*> parsedWires;

        foreach(Wire *w, wires) {
            if(parsedWires.contains(w)) {
                continue;
            }

            QList<Wire*> equi;
            w->getConnectedWires(equi);

            // Equipotential net, id = QString::number(equiId++)
            foreach(Wire *wire, equi) {
                /*! \todo Here we must do some logic to group all nets with
                 *  the same name (name = wireId++) into only one net number
                 *  and propagate it to all component lines.
                 */
            }

            parsedWires += equi;
        }

    }

} // namespace Caneda
