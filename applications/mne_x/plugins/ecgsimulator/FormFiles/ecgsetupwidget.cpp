//=============================================================================================================
/**
* @file     ecgsetupwidget.cpp
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     February, 2013
*
* @section  LICENSE
*
* Copyright (C) 2013, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of the Massachusetts General Hospital nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MASSACHUSETTS GENERAL HOSPITAL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Contains the implementation of the ECGSetupWidget class.
*
*/

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "ecgsetupwidget.h"
#include "ecgaboutwidget.h"
#include "../ecgsimulator.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QDir>
#include <QDebug>


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace ECGSimulatorModule;


//*************************************************************************************************************
//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

ECGSetupWidget::ECGSetupWidget(ECGSimulator* simulator, QWidget* parent)
: QWidget(parent)
, m_pECGSimulator(simulator)
{
    ui.setupUi(this);

    connect(ui.m_qDoubleSpinBox_SamplingRate, SIGNAL(valueChanged(double)), this, SLOT(setSamplingRate(double)));
    connect(ui.m_qSpinBox_Downsampling, SIGNAL(valueChanged(int)), this, SLOT(setDownsamplingRate(int)));


    QString path(m_pECGSimulator->m_qStringResourcePath+"data/");

    QDir directory = QDir(path);
    QStringList files;
    QString fileName("*.txt");
    files = directory.entryList(QStringList(fileName),
                                QDir::Files | QDir::NoSymLinks);

    ui.m_qComboBox_Channel_1->addItems(files);
    ui.m_qComboBox_Channel_2->addItems(files);
    ui.m_qComboBox_Channel_3->addItems(files);

    connect(ui.m_qComboBox_Channel_1, SIGNAL(currentIndexChanged(int)), this, SLOT(setFileOfChannel_I()));
    connect(ui.m_qComboBox_Channel_2, SIGNAL(currentIndexChanged(int)), this, SLOT(setFileOfChannel_II()));
    connect(ui.m_qComboBox_Channel_3, SIGNAL(currentIndexChanged(int)), this, SLOT(setFileOfChannel_III()));

    connect(ui.m_qCheckBox_Channel_Enable_1, SIGNAL(toggled(bool)), this, SLOT(setEnabledChannel_I(bool)));
    connect(ui.m_qCheckBox_Channel_Enable_2, SIGNAL(toggled(bool)), this, SLOT(setEnabledChannel_II(bool)));
    connect(ui.m_qCheckBox_Channel_Enable_3, SIGNAL(toggled(bool)), this, SLOT(setEnabledChannel_III(bool)));

    connect(ui.m_qCheckBox_Channel_Visible_1, SIGNAL(toggled(bool)), this, SLOT(setVisibleChannel_I(bool)));
    connect(ui.m_qCheckBox_Channel_Visible_2, SIGNAL(toggled(bool)), this, SLOT(setVisibleChannel_II(bool)));
    connect(ui.m_qCheckBox_Channel_Visible_3, SIGNAL(toggled(bool)), this, SLOT(setVisibleChannel_III(bool)));

    connect(ui.m_qPushButton_About, SIGNAL(released()), this, SLOT(showAboutDialog()));


    QFile file(m_pECGSimulator->m_qStringResourcePath+"readme.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ui.m_qTextBrowser_Information->insertHtml(line);
        ui.m_qTextBrowser_Information->insertHtml("<br>");
    }
}


//*************************************************************************************************************

ECGSetupWidget::~ECGSetupWidget()
{

}


//*************************************************************************************************************

void ECGSetupWidget::initSamplingFactors()
{
    ui.m_qDoubleSpinBox_SamplingRate->setValue(m_pECGSimulator->m_fSamplingRate);
    ui.m_qSpinBox_Downsampling->setValue(m_pECGSimulator->m_iDownsamplingFactor);
}


//*************************************************************************************************************

void ECGSetupWidget::initSelectedChannelFile()
{
    int idx;
    idx = ui.m_qComboBox_Channel_1->findText(m_pECGSimulator->m_pECGChannel_ECG_I->getChannelFile());
    if(idx >= 0)
        ui.m_qComboBox_Channel_1->setCurrentIndex(idx);

    idx = ui.m_qComboBox_Channel_2->findText(m_pECGSimulator->m_pECGChannel_ECG_II->getChannelFile());
    if(idx >= 0)
        ui.m_qComboBox_Channel_2->setCurrentIndex(idx);

    idx = ui.m_qComboBox_Channel_3->findText(m_pECGSimulator->m_pECGChannel_ECG_III->getChannelFile());
    if(idx >= 0)
        ui.m_qComboBox_Channel_3->setCurrentIndex(idx);

}


//*************************************************************************************************************

void ECGSetupWidget::initChannelStates()
{
    setEnabledChannel_I(m_pECGSimulator->m_pECGChannel_ECG_I->isEnabled());
    setVisibleChannel_I(m_pECGSimulator->m_pECGChannel_ECG_I->isVisible());

    setEnabledChannel_II(m_pECGSimulator->m_pECGChannel_ECG_II->isEnabled());
    setVisibleChannel_II(m_pECGSimulator->m_pECGChannel_ECG_II->isVisible());

    setEnabledChannel_III(m_pECGSimulator->m_pECGChannel_ECG_III->isEnabled());
    setVisibleChannel_III(m_pECGSimulator->m_pECGChannel_ECG_III->isVisible());
}



//*************************************************************************************************************

void ECGSetupWidget::setSamplingRate(double value)
{
    m_pECGSimulator->m_fSamplingRate = value;
}


//*************************************************************************************************************

void ECGSetupWidget::setDownsamplingRate(int value)
{
    m_pECGSimulator->m_iDownsamplingFactor = value;
}

//*************************************************************************************************************

void ECGSetupWidget::setEnabledChannel_I(bool state)
{
    m_pECGSimulator->m_pECGChannel_ECG_I->setEnabled(state);
    ui.m_qCheckBox_Channel_Enable_1->setChecked(state);
    ui.m_qLabel_Channel_1->setEnabled(state);
    ui.m_qCheckBox_Channel_Visible_1->setEnabled(state);
    ui.m_qComboBox_Channel_1->setEnabled(state);
}


//*************************************************************************************************************

void ECGSetupWidget::setEnabledChannel_II(bool state)
{
    m_pECGSimulator->m_pECGChannel_ECG_II->setEnabled(state);
    ui.m_qCheckBox_Channel_Enable_2->setChecked(state);
    ui.m_qLabel_Channel_2->setEnabled(state);
    ui.m_qCheckBox_Channel_Visible_2->setEnabled(state);
    ui.m_qComboBox_Channel_2->setEnabled(state);
}


//*************************************************************************************************************

void ECGSetupWidget::setEnabledChannel_III(bool state)
{
    m_pECGSimulator->m_pECGChannel_ECG_III->setEnabled(state);
    ui.m_qCheckBox_Channel_Enable_3->setChecked(state);
    ui.m_qLabel_Channel_3->setEnabled(state);
    ui.m_qCheckBox_Channel_Visible_3->setEnabled(state);
    ui.m_qComboBox_Channel_3->setEnabled(state);
}


//*************************************************************************************************************

void ECGSetupWidget::setVisibleChannel_I(bool state)
{
    m_pECGSimulator->m_pECGChannel_ECG_I->setVisible(state);
    ui.m_qCheckBox_Channel_Visible_1->setChecked(state);
}


//*************************************************************************************************************

void ECGSetupWidget::setVisibleChannel_II(bool state)
{
    m_pECGSimulator->m_pECGChannel_ECG_II->setVisible(state);
    ui.m_qCheckBox_Channel_Visible_2->setChecked(state);
}


//*************************************************************************************************************

void ECGSetupWidget::setVisibleChannel_III(bool state)
{
    m_pECGSimulator->m_pECGChannel_ECG_III->setVisible(state);
    ui.m_qCheckBox_Channel_Visible_3->setChecked(state);
}


//*************************************************************************************************************

void ECGSetupWidget::setFileOfChannel_I()
{
    m_pECGSimulator->m_pECGChannel_ECG_I->setChannelFile(ui.m_qComboBox_Channel_1->currentText());
}


//*************************************************************************************************************

void ECGSetupWidget::setFileOfChannel_II()
{
    m_pECGSimulator->m_pECGChannel_ECG_II->setChannelFile(ui.m_qComboBox_Channel_2->currentText());
}


//*************************************************************************************************************

void ECGSetupWidget::setFileOfChannel_III()
{
    m_pECGSimulator->m_pECGChannel_ECG_III->setChannelFile(ui.m_qComboBox_Channel_3->currentText());
}


//*************************************************************************************************************

void ECGSetupWidget::showAboutDialog()
{
    ECGAboutWidget aboutDialog(this);
    aboutDialog.exec();
}
