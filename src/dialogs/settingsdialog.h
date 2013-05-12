/***************************************************************************
 * Copyright (C) 2006-2009 Xavier Guerrin                                  *
 * Copyright (C) 2009 by Pablo Daniel Pareja Obregon                       *
 * This file was part of QElectroTech and modified by Pablo Daniel Pareja  *
 * Obregon to be included in Caneda.                                       *
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

#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include "settingspages.h"

#include <QDialog>

class QDialogButtonBox;
class QListWidget;
class QListWidgetItem;
class QStackedWidget;

namespace Caneda
{

    /*!
     * \brief This class represents the configuration dialog of Caneda.
     *
     * This dialog is a modal dialog showing setup or configuration pages. Each
     * configuration page should provide an icon and a title, along with a set
     * of different configuration options.
     */
    class SettingsDialog : public QDialog
    {
        Q_OBJECT

    public:
        SettingsDialog(QList<SettingsPage *> pages, const char *title,
                QWidget *parent = 0);

    public Q_SLOTS:
        void changePage(QListWidgetItem *, QListWidgetItem *);
        void applyConf();

    private:
        void buildPagesList();

    private:
        QListWidget *pages_list;
        QStackedWidget *pages_widget;
        QDialogButtonBox *buttons;
        QList<SettingsPage *> pages;
    };

} // namespace Caneda

#endif //SETTINGS_DIALOG_H
