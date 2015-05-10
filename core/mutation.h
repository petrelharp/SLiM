//
//  mutation.h
//  SLiM
//
//  Created by Ben Haller on 12/13/14.
//  Copyright (c) 2014 Philipp Messer.  All rights reserved.
//	A product of the Messer Lab, http://messerlab.org/software/
//

//	This file is part of SLiM.
//
//	SLiM is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
//	SLiM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License along with SLiM.  If not, see <http://www.gnu.org/licenses/>.

/*
 
 The class Mutation represents a single mutation, defined by its type, its position on the chromosome, and its selection coefficient.
 Mutations are also tagged with the subpopulation and generation in which they arose.
 
 */

#ifndef __SLiM__mutation__
#define __SLiM__mutation__


#include <iostream>

#include "mutation_type.h"
#include "slim_global.h"


class Mutation
{
	//	This class has its copy constructor and assignment operator disabled, to prevent accidental copying.

public:
	
	SLIMCONST MutationType *mutation_type_ptr_;			// mutation type identifier
	const int32_t position_;							// position on the chromosome
	const float selection_coeff_;						// selection coefficient
	const int32_t subpop_index_;						// subpopulation in which mutation arose
	const int32_t generation_;							// generation in which mutation arose
	mutable int32_t reference_count_;					// a count of the number of occurrences of this mutation; valid only at generation end, after ManageMutationReferencesAndRemoveFixedMutations()
#ifdef SLIMGUI
	const uint64_t mutation_id_;						// a unique id for each mutation, used to track mutations in SLiMgui
	mutable int32_t gui_reference_count_;				// a count of the number of occurrences of this mutation within the selected subpopulations in SLiMgui, valid at generation end
	mutable int32_t gui_scratch_reference_count;		// an additional refcount used for temporary tallies by SLiMgui, valid only when explicitly updated
#endif
	
	Mutation(const Mutation&) = delete;					// no copying
	Mutation& operator=(const Mutation&) = delete;		// no copying
	Mutation(void) = delete;							// no null construction; Mutation is an immutable class
	Mutation(SLIMCONST MutationType *p_mutation_type_ptr, int p_position, double p_selection_coeff, int p_subpop_index, int p_generation);
	
#if DEBUG_MUTATIONS
	~Mutation();										// destructor, if we are debugging
#endif
};

// true if M1 has an earlier (smaller) position than M2
inline bool operator<(const Mutation &p_mutation1, const Mutation &p_mutation2)
{
	return (p_mutation1.position_ < p_mutation2.position_);
}

// like operator< but with pointers; used for sort() among other things
inline bool CompareMutations(const Mutation *p_mutation1, const Mutation *p_mutation2)
{
	return (p_mutation1->position_ < p_mutation2->position_);
}

// true if M1 and M2 have the same position, type, and selection coefficient
inline bool operator==(const Mutation &p_mutation1, const Mutation &p_mutation2)
{
	return (p_mutation1.position_ == p_mutation2.position_ &&
			p_mutation1.mutation_type_ptr_ == p_mutation2.mutation_type_ptr_ &&
			p_mutation1.selection_coeff_ == p_mutation2.selection_coeff_);
}

// like operator== but with pointers; used for unique() among other things
inline bool EqualMutations(const Mutation *p_mutation1, const Mutation *p_mutation2)
{
	return (p_mutation1->position_ == p_mutation2->position_ &&
			p_mutation1->mutation_type_ptr_ == p_mutation2->mutation_type_ptr_ &&
			p_mutation1->selection_coeff_ == p_mutation2->selection_coeff_);
}

// support stream output of Mutation, for debugging
std::ostream &operator<<(std::ostream &p_outstream, const Mutation &p_mutation);


#endif /* defined(__SLiM__mutation__) */





































































