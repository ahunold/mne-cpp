//=============================================================================================================
/**
* @file     annotationset.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     July, 2012
*
* @section  LICENSE
*
* Copyright (C) 2012, Christoph Dinh and Matti Hamalainen. All rights reserved.
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
* @brief    AnnotationSet class declaration
*
*/

#ifndef ANNOTATION_SET_H
#define ANNOTATION_SET_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "fs_global.h"
#include "annotation.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QString>
#include <QSharedPointer>
#include <QMap>


//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================

#include <Eigen/Core>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE FSLIB
//=============================================================================================================

namespace FSLIB
{

//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace Eigen;


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

class SurfaceSet;


//=============================================================================================================
/**
* Annotation set
*
* @brief Annotation set
*/
class FSSHARED_EXPORT AnnotationSet
{
public:
    typedef QSharedPointer<AnnotationSet> SPtr;            /**< Shared pointer type for AnnotationSet. */
    typedef QSharedPointer<const AnnotationSet> ConstSPtr; /**< Const shared pointer type for AnnotationSet. */

    //=========================================================================================================
    /**
    * Default constructor
    */
    AnnotationSet();

    //=========================================================================================================
    /**
    * Constructs an annotation set by assembling given annotations
    *
    * @param[in] p_sLHAnnotation    Left hemisphere annotation
    * @param[in] p_sRHAnnotation    Right hemisphere annotation
    */
    explicit AnnotationSet(const Annotation& p_sLHAnnotation, const Annotation& p_sRHAnnotation);

    //=========================================================================================================
    /**
    * Constructs an annotation set by reading from annotation files
    *
    * @param[in] p_sLHFileName  Left hemisphere annotation file
    * @param[in] p_sRHFileName  Right hemisphere annotation file
    */
    explicit AnnotationSet(const QString& p_sLHFileName, const QString& p_sRHFileName);

    //=========================================================================================================
    /**
    * Destroys the annotation set.
    */
    ~AnnotationSet(){}

    //=========================================================================================================
    /**
    * Initializes the AnnotationSet.
    */
    void clear();

    //=========================================================================================================
    /**
    * Reads different annotation files and assembles them to a AnnotationSet
    *
    * @param[in] p_sLHFileName  Left hemisphere annotation file
    * @param[in] p_sRHFileName  Right hemisphere annotation file
    * @param[out] p_AnnotationSet   The read annotation set
    *
    * @return true if succesfull, false otherwise
    */
    static bool read(const QString& p_sLHFileName, const QString& p_sRHFileName, AnnotationSet &p_AnnotationSet);

    //=========================================================================================================
    /**
    * python labels_from_parc
    *
    * Converts annotation to a label list and colortable
    *
    * @param[in] p_surfSet              the SurfaceSet to read the vertex positions from
    * @param[out] p_qListLabels         the converted labels are appended to a given list. Stored data are not affected.
    * @param[out] p_qListLabelRGBAs     the converted label RGBAs are appended to a given list. Stored data are not affected.
    *
    * @return true if successful, false otherwise
    */
    bool toLabels(const SurfaceSet &p_surfSet, QList<Label> &p_qListLabels, QList<RowVector4i> &p_qListLabelRGBAs) const;

    //=========================================================================================================
    /**
    * Subscript operator [] to access annotation by index
    *
    * @param[in] idx    the hemisphere index (0 or 1).
    *
    * @return Annotation related to the parameter index.
    */
    Annotation& operator[] (qint32 idx);

    //=========================================================================================================
    /**
    * Subscript operator [] to access annotation by identifier
    *
    * @param[in] idt    the hemisphere identifier ("lh" or "rh").
    *
    * @return Annotation related to the parameter identifier.
    */
    Annotation& operator[] (QString idt);

private:
    QMap<qint32, Annotation> m_qMapAnnots;   /**< Hemisphere annotations (lh = 0; rh = 1). */

};

} // NAMESPACE

#endif // ANNOTATION_SET_H
