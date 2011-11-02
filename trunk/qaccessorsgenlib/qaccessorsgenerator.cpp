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

#include "qaccessorsgenerator.h"

const QString QAccessorsGenerator::DefaultMemberPrefix = "_";

#define QSTRING_TYPE    "QString"
#define BOOL_TYPE   "bool"



QAccessorsGenerator::QAccessorsGenerator()
{
}

QAccessorsGenerator::~QAccessorsGenerator()
{
}

QAccessorsGenerator *QAccessorsGenerator::createInstance()
{
    return new QAccessorsGenerator();
}


QAccessorsGeneratorsResult *QAccessorsGenerator::generate(QAccessorsGeneratorsInputParameters *inputParameters, QList<QAccessorsGeneratorsPropertyInfo*> &inputToGenerate )
{
    QAccessorsGeneratorsResult *results = new QAccessorsGeneratorsResult();
    if( NULL != results ) {
        foreach( QAccessorsGeneratorsPropertyInfo* input, inputToGenerate ) {
            QAccessorsGeneratorsOutput *out = innerGenerate(inputParameters, input );
            if( NULL == out ) {
                results->setError();
                return results;
            }
            results->generated.insert(out->id, out );
        }
    }
    return results;
}


QAccessorsGeneratorsResult *QAccessorsGenerator::generate(QAccessorsGeneratorsInputParameters *inputParameters, QAccessorsGeneratorsPropertyInfo* inputToGenerate )
{
    QAccessorsGeneratorsResult *results = new QAccessorsGeneratorsResult();
    if( NULL != results ) {
        QAccessorsGeneratorsOutput *out = innerGenerate(inputParameters, inputToGenerate );
        if( NULL == out ) {
            results->setError();
            return results;
        }
        results->generated.insert(out->id, out );
    }
    return results;
}


QAccessorsGeneratorsOutput *QAccessorsGenerator::innerGenerate(QAccessorsGeneratorsInputParameters *inputParameters, QAccessorsGeneratorsPropertyInfo* methodsInfo )
{
    QAccessorsGeneratorsOutput *result = new QAccessorsGeneratorsOutput();
    if( NULL == result ) {
        return NULL;
    }
    WorkingInfo info;
    result->id = methodsInfo->id;
    parseClass(info, inputParameters, methodsInfo, result);
    // declaration
    generateDeclarations(info, inputParameters, methodsInfo, result );
    // implementation
    generateImplementation(info, inputParameters, methodsInfo, result );
    return result;
}

void QAccessorsGenerator::parseClass(WorkingInfo &info, QAccessorsGeneratorsInputParameters *inputParameters, QAccessorsGeneratorsPropertyInfo* methodsInfo, QAccessorsGeneratorsOutput *outInfo)
{
    info.firstLetterUCName = methodsInfo->name.at(0).toUpper();
    if( methodsInfo->name.length() > 1 ) {
        info.firstLetterUCName.append(methodsInfo->name.mid(1));
    }

    if( methodsInfo->type == QSTRING_TYPE) {
        info.isReference = true ;
    } else if( methodsInfo->type == BOOL_TYPE) {
        info.useIs = true ;
    }

    outInfo->member = methodsInfo->name;
    if( inputParameters->useMemberPrefix ) {
        outInfo->member.prepend(inputParameters->memberPrefix);
    } else {
        outInfo->member.prepend(DefaultMemberPrefix);
    }
    outInfo->setterFunction = "set";
    outInfo->setterFunction.append(info.firstLetterUCName);

    if( info.useIs ) {
        outInfo->getterFunction = "is";
        outInfo->getterFunction.append(info.firstLetterUCName);
    } else {
        outInfo->getterFunction = methodsInfo->name ;
    }
}


void QAccessorsGenerator::generateDeclarations(WorkingInfo &info, QAccessorsGeneratorsInputParameters *inputParameters, QAccessorsGeneratorsPropertyInfo* methodsInfo, QAccessorsGeneratorsOutput * outParam )
{
    // property TODO:NOTIFY SCRIPTABLE DESIGNABLE STORED USER CONSTANT FINAL
    outParam->propertyDeclaration = QString("Q_PROPERTY(%1 %2 READ %3 WRITE %4)").arg(methodsInfo->type).arg(methodsInfo->name).arg(outParam->getterFunction).arg(outParam->setterFunction);

    // setter
    outParam->setterDeclaration = QString("void %1(const %2%3 value);").arg(outParam->setterFunction).arg(methodsInfo->type).arg((info.isReference?"&":""));

    // getter
    outParam->getterDeclaration = QString("%1 %2();").arg(methodsInfo->type).arg(outParam->getterFunction);

}

void QAccessorsGenerator::generateImplementation(WorkingInfo &info, QAccessorsGeneratorsInputParameters *inputParameters, QAccessorsGeneratorsPropertyInfo* methodsInfo, QAccessorsGeneratorsOutput * outParam )
{
    // implementation
    outParam->setterImplementation = QString("void %1::%2(const %3%4 value)\n")
                        .arg(methodsInfo->className)
                        .arg(outParam->setterFunction)
                        .arg(methodsInfo->type)
                        .arg((info.isReference?"&":""));
    outParam->setterImplementation.append("{\n");
    outParam->setterImplementation.append( QString("\t%1 = value ;\n").arg(outParam->member) );
    outParam->setterImplementation.append("}\n");

    outParam->getterImplementation = QString("%1 %2::%3()\n").arg(methodsInfo->type).arg(methodsInfo->className).arg(outParam->getterFunction);
    outParam->getterImplementation.append("{\n");
    outParam->getterImplementation.append(QString("\treturn %1 ;\n").arg(outParam->member));
    outParam->getterImplementation.append("}\n");
}


/********************
    // property TODO:NOTIFY SCRIPTABLE DESIGNABLE STORED USER CONSTANT FINAL
    QString property = QString("Q_PROPERTY(%1 %2 READ %3 WRITE %4)").arg(methodsInfo->type).arg(methodsInfo->name).arg(getterFunction).arg(setterFunction);
}



void generateDeclarations(QAccessorsGeneratorsInputParameters *inputParameters, QAccessorsGeneratorsPropertyInfo* methodsInfo, QAccessorsGeneratorsOutput * outParam )
{
    // name of the member variable
    QString member ;
    // name of the setter function
    QString setterFunction;
    // name of the getter function
    QString getterFunction;
    // if true the input value is a reference
    bool isReference = false;
    // use isName() getter instead of name()
    bool useIs = false;
    // name with the first letter Upper case
    QString firstLetterUCName;

    firstLetterUCName = methodsInfo->name.at(0).toUpper();
    if( methodsInfo->name.length() > 1 ) {
        firstLetterUCName.append(methodsInfo->name.mid(1));
    }

    if( methodsInfo->type == QSTRING_TYPE) {
        isReference = true ;
    } else if( methodsInfo->type == BOOL_TYPE) {
        useIs = true ;
    }

    member = methodsInfo->name;
    if( inputParameters->useMemberPrefix ) {
        member.prepend(inputParameters->memberPrefix);
    } else {
        member.prepend(DefaultMemberPrefix);
    }
    setterFunction = "set";
    setterFunction.append(firstLetterUCName);

    if( useIs ) {
        getterFunction = "is";
        getterFunction.append(firstLetterUCName);
    } else P
        getterFunction = name ;
    }

    // property TODO:NOTIFY SCRIPTABLE DESIGNABLE STORED USER CONSTANT FINAL
    QString property = QString("Q_PROPERTY(%1 %2 READ %3 WRITE %4)").arg(methodsInfo->type).arg(methodsInfo->name).arg(getterFunction).arg(setterFunction);

    // setter
    QString setterDeclaration = QString("void %1(const %2%3 value);").arg(setterFunction).arg(methodInfo.type).arg(isReference?"&":""));

    // getter
    QString getterDeclaration = QString("%1 %2();").arg(methodInfo.type).arg(getterFunction);

    // implementation
    QString setterImplementation = QString("void %1::%2(const %2%3 value)\n").arg(methodInfo.className).arg(setterFunction).arg(methodInfo.type).arg(isReference?"&":""));
    setterImplementation.append("{\n");
    setterImplementation.append( QString("\t %1 = value ;\n").arg(member);
    setterImplementation.append("}\n");

    QString getterImplementation = QString("%1 %2::%3();").arg(methodInfo.type).arg(methodInfo.className).arg(getterFunction).arg(methodInfo.type).arg(isReference?"&":""));
}

void generateImplementation(QAccessorsGeneratorsInputParameters *inputParameters, QAccessorsGeneratorsPropertyInfo* inputToGenerate, QAccessorsGeneratorsOutput * outParam )
{
    //TODO: if( tipo bool )
    // setter
    outParam->commentDeclaration = QString("void set%1%2(const %3 value);").arg(), toupper(argv[PNAME][0]), &argv[PNAME][1], argv[TYPE] ));

    // getter
    printf( "%s %s();\n", argv[TYPE], argv[PNAME]);
}

printf("\n");
printf( "void ::set%c%s(const %s value)\n", toupper(argv[PNAME][0]), &argv[PNAME][1], argv[TYPE] );
printf("{\n");
********************************************/
