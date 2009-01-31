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

#ifndef _CFKFEATURES__H__
#define _CFKFEATURES__H__

#include "features/RealFeatures.h"
#include "distributions/hmm/HMM.h"

/** The class FKFeatures implements Fischer kernel features obtained from
 * two Hidden Markov models and was used in
 *
 * K. Tsuda, M. Kawanabe, G. Raetsch, S. Sonnenburg, and K.R. Mueller. A new
 * discriminative kernel from probabilistic models. Neural Computation,
 * 14:2397-2414, 2002.
 *
 * which also has the details.
 *
 * Note that FK-features are computed on the fly, so to be effective feature
 * caching should be enabled.
 *
 * It inherits its functionality from CSimpleFeatures, which should be
 * consulted for further reference.
 */
class CFKFeatures: public CRealFeatures
{
	public:
		/** constructor
		 *
		 * @param size cache size
		 * @param p positive HMM
		 * @param n negative HMM
		 */
		CFKFeatures(int32_t size, CHMM* p, CHMM* n);

		/** copy constructor */
		CFKFeatures(const CFKFeatures &orig);

		virtual ~CFKFeatures();

		/** set HMMs
		 *
		 * @param p positive HMM
		 * @param n negative HMM
		 */
		void set_models(CHMM* p, CHMM* n);

		/** set weight a
		 *
		 * @param a weight a
		 */
		inline void set_a(float64_t a)
		{
			weight_a=a;
		}

		/** get weight a
		 *
		 * @return weight a
		 */
		inline float64_t get_a()
		{
			return weight_a;
		}

		/** set feature matrix
		 *
		 * @return something floaty
		 */
		virtual float64_t* set_feature_matrix();

		/** set opt a
		 *
		 * @param a a
		 * @return something floaty
		 */
		float64_t set_opt_a(float64_t a=-1);

		/** get weight_a
		 *
		 * @return weight_a
		 */
		inline float64_t get_weight_a() { return weight_a; };

		/** @return object name */
		inline virtual const char* get_name() { return "FKFeatures"; }

	protected:
		/** compute feature vector
		 *
		 * @param num num
		 * @param len len
		 * @param target
		 * @return something floaty
		 */
		virtual float64_t* compute_feature_vector(
			int32_t num, int32_t& len, float64_t* target=NULL);

		/** computes the feature vector to the address addr
		 *
		 * @param addr address
		 * @param num num
		 * @param len len
		 */
		void compute_feature_vector(float64_t* addr, int32_t num, int32_t& len);

		/** deriv a
		 *
		 * @param a a
		 * @param dimension dimension
		 */
		float64_t deriv_a(float64_t a, int32_t dimension=-1) ;

	protected:
		/** positive HMM */
		CHMM* pos;
		/** negative HMM */
		CHMM* neg;
		/** positive prob */
		float64_t* pos_prob;
		/** negative prob */
		float64_t* neg_prob;
		/** weight a */
		float64_t weight_a;
};
#endif
