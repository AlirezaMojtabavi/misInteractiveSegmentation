/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Copyright (C) 2005-2010 The Voreen Team. <http://www.voreen.org>   *
 *                                                                    *
 * This file is part of the Voreen software package. Voreen is free   *
 * software: you can redistribute it and/or modify it under the terms *
 * of the GNU General Public License version 2 as published by the    *
 * Free Software Foundation.                                          *
 *                                                                    *
 * Voreen is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * in the file "LICENSE.txt" along with this program.                 *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 * The authors reserve all rights not expressly granted herein. For   *
 * non-commercial academic use see the license exception specified in *
 * the file "LICENSE-academic.txt". To get information about          *
 * commercial licensing please contact the authors.                   *
 *                                                                    *
 **********************************************************************/

#ifndef VRN_MULTIVOLUMEPROXYGEOMETRY_H
#define VRN_MULTIVOLUMEPROXYGEOMETRY_H

#include "processor.h"
#include "allports.h"

#include "meshlistgeometry.h"
#include "VoreenMacroes.h"

namespace voreen {

/**
 * Provides a cube mesh proxy geometry for multi-volume raycasting.
 *
 * @see MeshEntryExitPoints
 * @see MeshClipping
 * @see MultiVolumeRaycaster
 */
class   VOREENEXPORTS MultiVolumeProxyGeometry : public Processor {

public:
    MultiVolumeProxyGeometry();
    virtual ~MultiVolumeProxyGeometry();
    virtual Processor* create() const;

    virtual std::string getClassName() const  { return "MultiVolumeProxyGeometry"; }
    virtual std::string getCategory() const   { return "Volume Proxy Geometry"; }
    virtual CodeState getCodeState() const    { return CODE_STATE_STABLE; }
    virtual std::string getProcessorInfo() const;
	virtual void process();
	virtual void initialize() throw (VoreenException);
	voreen::VolumePort* GetInport() ;
	MeshListGeometry* GetGeometry() const;
	void TestResult();
	void ResetVolumeData(){this->volumeData.clear();};
	void  AddVolumeHandle(VolumeHandle*  volumeHnd);

protected:
   
    virtual void deinitialize() throw (VoreenException);

    /**
     * Cube mesh proxy geometry.
     */
    MeshListGeometry* geometry_;
	MeshListGeometry* Geometry() const { return geometry_; }
     /**
     * Inport for the dataset.
     */
    std::vector<VolumeHandle*>  volumeData;;
	
    /**
     * Outport for the cube mesh proxy geometry.
     */
    GeometryPort outport_;

	//jalal
	virtual bool isReady() const;

};

} // namespace

#endif // VRN_MULTIVOLUMEPROXYGEOMETRY_H
