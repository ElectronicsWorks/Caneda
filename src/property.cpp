/***************************************************************************
 * Copyright (C) 2007 by Gopala Krishna A <krishna.ggk@gmail.com>          *
 * Copyright (C) 2012 by Pablo Daniel Pareja Obregon                       *
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

#include "property.h"

#include "global.h"
#include "xmlutilities.h"

#include <QDebug>

namespace Caneda
{
    //! \brief Constructor.
    PropertyData::PropertyData()
    {
        name = QString();
        value = QString();
        description = QString();
        visible = false;
    }

    //! \brief Copy constructor
    PropertyData::PropertyData(const PropertyData& p) : QSharedData(p)
    {
        name = p.name;
        value = p.value;
        description = p.description;
        visible = p.visible;
    }

    /*!
     * \brief Constructs a property object
     *
     * \param _name Name of property object.
     * \param _value The default value of property.
     * \param _description Description of property.
     * \param _visible Visibility of property object(item)
     */
    Property::Property(const QString& _name,
                       const QString& _value,
                       const QString& _description,
                       bool _visible)
    {
        d = new PropertyData;
        d->name = _name;
        d->value = _value;
        d->description = _description;
        d->visible = _visible;
    }

    //! \brief Construct property from shared data.
    Property::Property(QSharedDataPointer<PropertyData> data) : d(data)
    {
    }

    /*!
     * \brief Method used to create a property from an xml file.
     *
     * \param reader XmlReader which is in use for parsing.
     */
    Property Property::loadProperty(Caneda::XmlReader *reader)
    {
        Q_ASSERT(reader->isStartElement() && reader->name() == "property");
        QSharedDataPointer<PropertyData> data(new PropertyData);

        QXmlStreamAttributes attributes = reader->attributes();

        data->name = attributes.value("name").toString();
        if(data->name.isEmpty()) {
            reader->raiseError("Couldn't find name attribute in property description");
            return Property();
        }

        QString visible = attributes.value("visible").toString();
        data->visible = !(visible.isEmpty() || visible == "false");

        data->value = attributes.value("default").toString();

        while(!reader->atEnd()) {
            reader->readNext();

            if(reader->isEndElement()) {
                break;
            }

            if(reader->isStartElement()) {
                if(reader->name() == "description") {
                    data->description = reader->readLocaleText(Caneda::localePrefix());
                }
                else {
                    reader->readUnknownElement();
                }
            }
        }

        return Property(data);
    }

} // namespace Caneda
