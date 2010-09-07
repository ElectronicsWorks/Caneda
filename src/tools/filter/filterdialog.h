/***************************************************************************
 * Copyright (C) 2010 by Pablo Daniel Pareja Obregon                       *
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

#ifndef FILTER_DIALOG_H
#define FILTER_DIALOG_H

#include "ui_filterdialog.h"

namespace Caneda
{
    class FilterDialog : public QDialog
    {
        Q_OBJECT

    public:
        FilterDialog(QWidget *parent = 0);
        ~FilterDialog();

    private slots:
        void slotCalculate();
        void slotTypeChanged();
        void slotClassChanged();

    private:
        Ui::FilterDialog ui;
    };

} // namespace Caneda

#endif //FILTER_DIALOG_H