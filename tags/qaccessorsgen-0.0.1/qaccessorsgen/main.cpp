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

#include <QtCore/QCoreApplication>
#include <stdio.h>
#include "qaccessorsgenerator.h"

static void help();
static void error(const char *message);
static void generate( const char * className, const char * type, const char * name );
static void outputData( QAccessorsGeneratorsOutput *output, const char *type );

int main(int argc, char *argv[])
{
    if( argc < 3 ) {
        help();
        return 1;
    }
    generate( argv[1], argv[2], argv[3] );
    return 0;
}

static void help()
{
    printf("usage: parameters are className, type, name\n");
}

static void error(const char *message)
{
    printf("***** ERROR\n");
    printf("cause: %s\n", message );
    printf("******************\n");
}

static void generate( const char * className, const char * type, const char * name )
{
    QAccessorsGenerator *generator = QAccessorsGenerator::createInstance();
    QAccessorsGeneratorsPropertyInfo *info = QAccessorsGeneratorsPropertyInfo::createInstance();
    QAccessorsGeneratorsInputParameters *parameters = QAccessorsGeneratorsInputParameters::createInstance();

    bool isError = false;
    if( NULL == generator ) {
        error("unable to create generator instance");
        isError = true;
    }
    if( NULL == info ) {
        error("unable to create info instance");
        isError = true;
    }
    if( NULL == parameters ) {
        error("unable to create parameters instance");
        isError = true;
    }
    if( ! isError ) {
        info->id = "1";
        info->className = className;
        info->name = name ;
        info->type= type ;
        QList<QAccessorsGeneratorsPropertyInfo*> infos;
        infos.append(info);
        QAccessorsGeneratorsResult *results = generator->generate( parameters, infos );
        if( NULL == results ) {
            error("No result from generation");
            isError = true;
        } else {
            if( results->isError ) {
                error("Error in generation phase");
                isError = true;
            } else {
                outputData(results->generated["1"], type);
            }
            delete results;
        }
    }

    if( NULL != generator ) {
        delete generator ;
    }
    if( NULL != info ) {
        delete info ;
    }
    if( NULL != parameters ) {
        delete parameters ;
    }
}

static void outputData( QAccessorsGeneratorsOutput *output, const char *type )
{
    if( NULL == output ) {
        error("No data generated");
    }
    printf("----------------------------\n");
    printf("DECLARATIONS:\n");
    printf("%s %s;\n\n", type, output->member.toLatin1().data());
    printf("%s\n\n", output->propertyDeclaration.toLatin1().data());
    printf("%s\n\n", output->getterDeclaration.toLatin1().data());
    printf("%s\n\n", output->setterDeclaration.toLatin1().data());
    printf("----------------------------\n");
    printf("IMPLEMENTATION:\n");
    printf("%s\n\n", output->getterImplementation.toLatin1().data());
    printf("%s\n\n", output->setterImplementation.toLatin1().data());
    printf("----------------------------\n");
}
