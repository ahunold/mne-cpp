//=============================================================================================================
/**
* @file     progressbarwidget.h
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
* @brief    Contains the declaration of the ProgressBarWidget class.
*
*/

#ifndef PROGRESSBARWIDGET_H
#define PROGRESSBARWIDGET_H


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "xdisp_global.h"
#include "measurementwidget.h"
#include "ui_progressbarwidget.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QBrush>
#include <QFont>


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

namespace XMEASLIB
{
class ProgressBar;
}


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE XDISPLIB
//=============================================================================================================

namespace XDISPLIB
{


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace XMEASLIB;


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================


//=============================================================================================================
/**
* DECLARE CLASS ProgressBarWidget
*
* @brief The ProgressBarWidget class provides a progress bar display.
*/
class XDISPSHARED_EXPORT ProgressBarWidget : public MeasurementWidget
{
    Q_OBJECT

public:

    //=========================================================================================================
    /**
    * Constructs a ProgressBarWidget which is a child of parent.
    *
    * @param [in] pProgressBar pointer to ProgressBar measurement.
    * @param [in] parent pointer to parent widget; If parent is 0, the new ProgressBarWidget becomes a window. If parent is another widget, ProgressBarWidget becomes a child window inside parent. ProgressBarWidget is deleted when its parent is deleted.
    */
    ProgressBarWidget(QSharedPointer<ProgressBar> pProgressBar, QWidget *parent = 0);

    //=========================================================================================================
    /**
    * Destroys the ProgressBarWidget.
    */
    ~ProgressBarWidget();

    //=========================================================================================================
    /**
    * Is called when new data are available.
    * Inherited by IObserver.
    *
    * @param [in] pSubject pointer to Subject -> not used because its direct attached to the measurement.
    */
    virtual void update(Subject* pSubject);

    //=========================================================================================================
    /**
    * Initialise the ProgressBarWidget.
    */
    virtual void init();

    //=========================================================================================================
    /**
    * Is called to paint the progress bar of the ProgressBarWidget.
    *
    * @param [in] event pointer to PaintEvent -> not used.
    */
    virtual void paintEvent(QPaintEvent* event);

private:
    Ui::ProgressBarWidgetClass  ui;                 /**< Holds the user interface of the ProgressBar widget. */
    QSharedPointer<ProgressBar> m_pProgressBar;     /**< Holds ProgressBar measurement. */
    double                      m_dSegmentSize;     /**< Holds the segment size. */
    unsigned short              m_usXPos;           /**< Holds the horizontal start position. */
    QBrush                      m_Brush;            /**< Holds the progress bar brush. */
    QFont                       m_Font;             /**< Holds the progress bar text font. */
    QString                     m_Text;             /**< Holds the progress bar progress text. */
};

} // NAMESPACE

#endif // PROGRESSBARWIDGET_H
