/***************************************************************************
 *   This file is part of qaccessorsgen                                    *
 *   Copyright (C) 2011 by Luca Bellonda                                   *
 *   lbellonda _at_ gmail.com                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *    Boston, MA  02110-1301, USA.                                         *
 ***************************************************************************/

#ifndef QACCESSORSGENERATORSPROPERTYINFO_H
#define QACCESSORSGENERATORSPROPERTYINFO_H

#include "qaccessorsgenlib_global.h"

class QACCESSORSGENLIBSHARED_EXPORT QAccessorsGeneratorsPropertyInfo
{
public:
    QString id;
    QString type;
    QString name;
    QString className;

    explicit QAccessorsGeneratorsPropertyInfo();
public:
    ~QAccessorsGeneratorsPropertyInfo();
    static QAccessorsGeneratorsPropertyInfo *createInstance();
};

#endif // QACCESSORSGENERATORSPROPERTYINFO_H
