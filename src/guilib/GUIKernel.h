/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2008 Soeren Sonnenburg
 * Written (W) 1999-2008 Gunnar Raetsch
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef __GUIKERNEL__H
#define __GUIKERNEL__H

#include "lib/config.h"

#ifndef HAVE_SWIG
#include "base/SGObject.h"
#include "kernel/Kernel.h"

class CSGInterface;

class CGUIKernel : public CSGObject
{
 public:
 	/** constructor */
	CGUIKernel(CSGInterface* interface);

	/** destructor */
	~CGUIKernel();

	/** get active kernel */
	CKernel* get_kernel();
	/** set normalization */
	bool set_normalization(char* normalization, float64_t c=0.0);
	/** set active kernel */
	bool set_kernel(CKernel* kern);
	/** add kernel to a Combined kernel, creating one if necessary */
	bool add_kernel(CKernel* kern, float64_t weight=1);
	/** delete last kernel in combined kernel */
	bool del_last_kernel();

	/** initialize kernel */
	bool init_kernel(char* target);
	/** initialize kernel  optimization */
	bool init_kernel_optimization();
	/** delete kernel optimization */
	bool delete_kernel_optimization();
	/** load kernel initialization from file */
	bool load_kernel_init(char* filename);
	/** save kernel initialization to file */
	bool save_kernel_init(char* filename);
	/** save kernel (matrix) to file */
	bool save_kernel(char* filename);
	/** clean/r kernel */
	bool clean_kernel();
#ifdef USE_SVMLIGHT
	/** resize kernel cache */
	bool resize_kernel_cache(int32_t size);
#endif //USE_SVMLIGHT
	/** set optimization type */
	bool set_optimization_type(char* opt_type);
	/** precompute subkernels */
	bool precompute_subkernels();

	/** check if kernel is initialized */
	bool is_initialized() { return initialized; }

#ifdef HAVE_MINDY
	/** create a new MindyGram kernel */
	CKernel* CGUIKernel::create_mindygram(
		int32_t size=10, char* meas_str=NULL, char* norm_str=NULL,
		float64_t width=1, char* param_str=NULL)
#endif

	/** create Oligo kernel */
	CKernel* create_oligo(int32_t size, int32_t k, float64_t width);
	/** create a new Diag kernel */
	CKernel* create_diag(int32_t size=10, float64_t diag=1);
	/** create a new Const kernel */
	CKernel* create_const(int32_t size=10, float64_t c=1);
	/** create a new Custom kernel */
	CKernel* create_custom();
	/** create a new GaussianShift kernel */
	CKernel* create_gaussianshift(
		int32_t size=10, float64_t width=1, int32_t max_shift=0,
		int32_t shift_step=1);
	/** create a new SparseGaussian kernel */
	CKernel* create_sparsegaussian(int32_t size=10, float64_t width=1);
	/** create a new Gaussian kernel */
	CKernel* create_gaussian(int32_t size=10, float64_t width=1);
	/** create a new Sigmoid kernel */
	CKernel* create_sigmoid(
		int32_t size=10, float64_t gamma=0.01, float64_t coef0=0);
	/** create a new TPP kernel */
	CKernel* create_tppk(
		int32_t size, float64_t* km, int32_t rows, int32_t cols);
	/** create a new SparsePoly kernel */
	CKernel* create_sparsepoly(
		int32_t size=10, int32_t degree=2, bool inhomogene=false,
		bool normalize=true);
	/** create a new Poly kernel */
	CKernel* create_poly(
		int32_t size=10, int32_t degree=2, bool inhomogene=false,
		bool normalize=true);
	/** create a new (Simple)LocalityImprovedString kernel */
	CKernel* create_localityimprovedstring(
		int32_t size=10, int32_t length=3, int32_t inner_degree=3,
		int32_t outer_degree=1, EKernelType ktype=K_LOCALITYIMPROVED);
	/** create a new WeightedDegreeString kernel */
	CKernel* create_weighteddegreestring(
		int32_t size=10, int32_t order=3, int32_t max_mismatch=1,
		bool use_normalization=true, int32_t mkl_stepsize=1,
		bool block_computation=true, int32_t single_degree=-1);
	/** create a new WeightedDegreePositionString kernel */
	CKernel* create_weighteddegreepositionstring(
		int32_t size=10, int32_t order=3, int32_t max_mismatch=1,
		int32_t length=0, int32_t center=0, float64_t step=1);
	CKernel* create_weighteddegreepositionstring3(
		int32_t size=10, int32_t order=3, int32_t max_mismatch=1,
		int32_t* shifts=NULL, int32_t length=0, int32_t mkl_stepsize=1,
		float64_t* position_weights=NULL);
	CKernel* create_weighteddegreepositionstring2(
		int32_t size=10, int32_t order=3, int32_t max_mismatch=1,
		int32_t* shifts=NULL, int32_t length=0, bool use_normalization=true);
	/** create a new LocalAlignmentString kernel */
	CKernel* create_localalignmentstring(int32_t size=10);
	/** create a new FixedDegreeString kernel */
	CKernel* create_fixeddegreestring(int32_t size=10, int32_t d=3);
	/** create a new Chi2 kernel */
	CKernel* create_chi2(int32_t size=10, float64_t width=1);
	/** create a new WeightedCommWord/CommWord/CommULongString kernel */
	CKernel* create_commstring(
		int32_t size=10, bool use_sign=false, char* norm_str=NULL,
		EKernelType ktype=K_WEIGHTEDCOMMWORDSTRING);
	/** create a new MatchWordString kernel */
	CKernel* create_matchwordstring(
		int32_t size=10, int32_t d=3, bool normalize=true);
	/** create a new PolyMatchString kernel */
	CKernel* create_polymatchstring(
		int32_t size=10, int32_t degree=2, bool inhomogene=false,
		bool normalize=true);
	/** create a new PolyMatchWordString kernel */
	CKernel* create_polymatchwordstring(
		int32_t size=10, int32_t degree=2, bool inhomogene=false,
		bool normalize=true);
	/** create a new SalzbergWord kernel */
	CKernel* create_salzbergword(int32_t size=10);
	/** create a new HistogramWord kernel */
	CKernel* create_histogramword(int32_t size=10);
	/** create a new LinearByte kernel */
	CKernel* create_linearbyte(int32_t size=10, float64_t scale=-1);
	/** create a new LinearWord kernel */
	CKernel* create_linearword(int32_t size=10, float64_t scale=-1);
	/** create a new LinearString kernel */
	CKernel* create_linearstring(int32_t size=10, float64_t scale=-1);
	/** create a new Linear kernel */
	CKernel* create_linear(int32_t size=10, float64_t scale=-1);
	/** create a new SparseLinear kernel */
	CKernel* create_sparselinear(int32_t size=10, float64_t scale=-1);
	/** create a new Distance kernel */
	CKernel* create_distance(int32_t size=10, float64_t width=1);
	/** create a new Combined kernel */
	CKernel* create_combined(
		int32_t size=10, bool append_subkernel_weights=false);

	/** @return object name */
	inline virtual const char* get_name() { return "GUIKernel"; }

 protected:
	CKernel* kernel;
	CSGInterface* ui;
	bool initialized;

 private:
	float64_t* get_weights(int32_t order, int32_t max_mismatch);

};
#endif //HAVE_SWIG
#endif
