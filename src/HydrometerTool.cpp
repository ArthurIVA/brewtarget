/*
 * ConverterTool.cpp is part of Brewtarget, and is Copyright the following
 * authors 2009-2015
 * - Philip Greggory Lee <rocketman768@gmail.com>
 *
 * Brewtarget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Brewtarget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "HydrometerTool.h"
#include "unit.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpacerItem>
#include <math.h>
#include <brewtarget.h>
#include "BtLineEdit.h"

HydrometerTool::HydrometerTool(QWidget* parent) : QDialog(parent)
{
   doLayout();
   
   connect( pushButton_convert, SIGNAL(clicked()), this, SLOT(convert()) );
}

void HydrometerTool::doLayout()
{
   resize(279, 96);
   QHBoxLayout* hLayout = new QHBoxLayout(this);
      QFormLayout* formLayout = new QFormLayout();
         inputLabel = new QLabel(this);
         inputLineEdit = new QLineEdit(this);
            inputLineEdit->setMinimumSize(QSize(100, 0));
            inputLineEdit->setMaximumSize(QSize(128, 16777215));
         outputUnitsLabel = new QLabel(this);
         outputUnitsLineEdit = new BtTemperatureEdit(this);
            outputUnitsLineEdit->setMinimumSize(QSize(40, 0));
            outputUnitsLineEdit->setMaximumSize(QSize(40, 16777215));
         outputLabel = new QLabel(this);
         outputLineEdit = new QLabel(this);
            outputLineEdit->setMinimumSize(QSize(100, 0));
            outputLineEdit->setMaximumSize(QSize(128, 16777215));
           // outputLineEdit->setReadOnly(true);


         formLayout->setWidget(0, QFormLayout::LabelRole, inputLabel);
         formLayout->setWidget(0, QFormLayout::FieldRole, inputLineEdit);
         formLayout->setWidget(1, QFormLayout::LabelRole, outputUnitsLabel);
         formLayout->setWidget(1, QFormLayout::FieldRole, outputUnitsLineEdit);
         formLayout->setWidget(2, QFormLayout::LabelRole, outputLabel);
         formLayout->setWidget(2, QFormLayout::FieldRole, outputLineEdit);


         formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
      QVBoxLayout* vLayout = new QVBoxLayout();
         QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
         pushButton_convert = new QPushButton(this);
            pushButton_convert->setAutoDefault(false);
            pushButton_convert->setDefault(true);
         QSpacerItem* verticalSpacer2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
         vLayout->addItem(verticalSpacer);
         vLayout->addWidget(pushButton_convert);
         vLayout->addItem(verticalSpacer2);

         QSpacerItem* verticalSpacer3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
         vLayout->addItem(verticalSpacer3);

   hLayout->addLayout(formLayout);
   hLayout->addLayout(vLayout);


   retranslateUi();
}

void HydrometerTool::retranslateUi()
{
   setWindowTitle(tr("Hydrometer Tool"));
   inputLabel->setText(tr("SG Reading")); //TODO translation
   outputUnitsLabel->setText(tr("Temp"));
   outputLabel->setText(tr("Adjust SG"));

   pushButton_convert->setText(tr("Convert"));
#ifndef QT_NO_TOOLTIP
   inputLineEdit->setToolTip(tr("Measured gravity"));  //TODO translate
   outputUnitsLineEdit->setToolTip(tr("Temperature with units"));  //TODO translate
   outputLineEdit->setToolTip(tr("Corrected gravity"));  //TODO translate


#endif // QT_NO_TOOLTIP
}

void HydrometerTool::convert()
{
   //outputLineEdit->setText(Unit::convert(inputLineEdit->text(), outputUnitsLineEdit->text()));
    /*
    cg = corrected gravity

    mg = measured gravity

    tr = temperature at time of reading

    tc = calibration temperature of hydrometer*/


    double cg;
    double mg;
    QString tr_string;
    QString fahr = "F";
    double tr;
    double tc = 60;
    Unit *unit;
    double test;

    //tempVal->setObjectName(QStringLiteral("TempVal"));

    tr_string = outputUnitsLineEdit->text();

    //test = outputUnitsLineEdit->toSI();


   // test = unit->getUnitOrTempSystem();

    //tr_string = (Unit::convert(tr_string, "F")).toDouble();

    bool ok = false;

    tr_string = Unit::convert(outputUnitsLineEdit->text(), fahr);

    tr = outputUnitsLineEdit->toDouble(&ok);
    tr = outputUnitsLineEdit->toSI();

   // static QString convert(QString qstr, QString toUnit);


    // tr=tr_string.toDouble();

   // test = unit->getUnitOrTempSystem();

   // test = test;

    mg = inputLineEdit->text().toDouble();

    /*
    if(tr[tr.length]=="C")
    {
        println("Needs Converted");
    }
*/

    cg = mg * ((1.00130346 - 0.000134722124 * tr + 0.00000204052596 * pow(tr,2) - 0.00000000232820948 * pow(tr,3)) / (1.00130346 - 0.000134722124 * tc + 0.00000204052596 * pow(tc,2) - 0.00000000232820948 * pow(tc,3)));


    outputLineEdit->setText(QString::number(cg,'f',3));
}
