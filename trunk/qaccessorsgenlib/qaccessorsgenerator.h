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

#ifndef QACCESSORSGENERATOR_H
#define QACCESSORSGENERATOR_H

#include "qaccessorsgenlib_global.h"

#include "qaccessorsgeneratorsinputparameters.h"
#include "qaccessorsgeneratorspropertyinfo.h"
#include "qaccessorsgeneratorsoutput.h"
#include "qaccessorsgeneratorsresult.h"
#include "workinginfo.h"

class QACCESSORSGENLIBSHARED_EXPORT QAccessorsGenerator {

    static const QString DefaultMemberPrefix;
    QAccessorsGenerator();

    void parseClass(WorkingInfo &info, QAccessorsGeneratorsInputParameters *inputParameters, QAccessorsGeneratorsPropertyInfo* methodsInfo, QAccessorsGeneratorsOutput *outInfo);
    QAccessorsGeneratorsOutput *innerGenerate(QAccessorsGeneratorsInputParameters *inputParameters, QAccessorsGeneratorsPropertyInfo* inputToGenerate );
    void generateDeclarations(WorkingInfo &info, QAccessorsGeneratorsInputParameters *inputParameters, QAccessorsGeneratorsPropertyInfo* methodsInfo, QAccessorsGeneratorsOutput * outParam );
    void generateImplementation(WorkingInfo &info, QAccessorsGeneratorsInputParameters *inputParameters, QAccessorsGeneratorsPropertyInfo* methodsInfo, QAccessorsGeneratorsOutput * outParam );

public:
    ~QAccessorsGenerator();
    static QAccessorsGenerator *createInstance();
    /**
      result: the caller take ownership of the
       result. If result is NULL, not enough memory is
       available*/
    QAccessorsGeneratorsResult *generate(QAccessorsGeneratorsInputParameters *inputParameters, QList<QAccessorsGeneratorsPropertyInfo*> &inputToGenerate );
    QAccessorsGeneratorsResult *generate(QAccessorsGeneratorsInputParameters *inputParameters, QAccessorsGeneratorsPropertyInfo* inputToGenerate );
};

#endif // QACCESSORSGENERATOR_H
