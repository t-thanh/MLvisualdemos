// Copyright (C) 2009  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.
#ifndef DLIB_SVm_KERNEL_MATRIX_
#define DLIB_SVm_KERNEL_MATRIX_

#include <vector>
#include "kernel_matrix_abstract.h"
#include "../matrix.h"
#include "../algs.h"

namespace dlib
{

// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------

    namespace impl
    {
        template <typename kernel_type, typename T>
        inline const typename T::type& access ( const matrix_exp<T>& m, long i)
        {
            return m(i);
        }

        template <typename kernel_type, typename T, typename alloc>
        inline const T& access ( const std::vector<T,alloc>& m, long i)
        {
            return m[i];
        }

        template <typename kernel_type, typename T, typename alloc>
        inline const T& access ( const std_vector_c<T,alloc>& m, long i)
        {
            return m[i];
        }

        template <typename kernel_type>
        inline const typename kernel_type::sample_type& access ( 
            const typename kernel_type::sample_type& samp, 
            long 
        )
        {
            return samp;
        }

        // --------------------------------------------

        template <typename kernel_type, typename T>
        inline unsigned long size ( const matrix_exp<T>& m)
        {
            return m.size();
        }

        template <typename kernel_type, typename T, typename alloc>
        inline unsigned long size ( const std::vector<T,alloc>& m)
        {
            return m.size();
        }

        template <typename kernel_type, typename T, typename alloc>
        inline unsigned long size ( const std_vector_c<T,alloc>& m)
        {
            return m.size();
        }

        template <typename kernel_type>
        inline unsigned long size ( 
            const typename kernel_type::sample_type&  
        )
        {
            return 1;
        }

        // --------------------------------------------

        template <typename T>
        typename disable_if<is_matrix<T> >::type assert_is_vector(const T&)
        {}

        template <typename T>
        // This funny #ifdef thing is here because gcc sometimes gives a warning 
        // about v being unused otherwise.
#ifdef ENABLE_ASSERTS
        void assert_is_vector(const matrix_exp<T>& v)
#else
        void assert_is_vector(const matrix_exp<T>& )
#endif
        {
            // make sure requires clause is not broken
            DLIB_ASSERT(is_vector(v) == true,
                "\tconst matrix_exp kernel_matrix()"
                << "\n\t You have to supply this function with row or column vectors"
                << "\n\t v.nr(): " << v.nr()
                << "\n\t v.nc(): " << v.nc()
                );
        }

    }

    template <typename K, typename vect_type1, typename vect_type2>
    struct op_kern_mat : does_not_alias 
    {
        op_kern_mat( 
            const K& kern_, 
            const vect_type1& vect1_,
            const vect_type2& vect2_
        ) : 
            kern(kern_), 
            vect1(vect1_),
            vect2(vect2_) 
        {
            // make sure the requires clauses get checked eventually
            impl::assert_is_vector(vect1);
            impl::assert_is_vector(vect2);
        }

        const K& kern;
        const vect_type1& vect1;
        const vect_type2& vect2;

        typedef typename K::scalar_type type;

        const static long cost = 100;
        const static long NR = (is_same_type<vect_type1,typename K::sample_type>::value) ? 1 : 0;
        const static long NC = (is_same_type<vect_type2,typename K::sample_type>::value) ? 1 : 0;

        typedef const type const_ret_type;
        typedef typename K::mem_manager_type mem_manager_type;
        typedef row_major_layout layout_type;

        const_ret_type apply (long r, long c ) const 
        { 
            return kern(impl::access<K>(vect1,r), impl::access<K>(vect2,c)); 
        }

        long nr () const { return impl::size<K>(vect1); }
        long nc () const { return impl::size<K>(vect2); }
    }; 

// ----------------------------------------------------------------------------------------

    template <
        typename K,
        typename V1,
        typename V2 
        >
    const matrix_op<op_kern_mat<K,V1,V2> > kernel_matrix (
        const K& kern,
        const V1& v1,
        const V2& v2
        )
    {
        typedef op_kern_mat<K,V1,V2> op;
        return matrix_op<op>(op(kern,v1,v2));
    }
    
// ----------------------------------------------------------------------------------------

    template <
        typename K,
        typename V
        >
    const matrix_op<op_kern_mat<K,V,V> > kernel_matrix (
        const K& kern,
        const V& v
        )
    {
        typedef op_kern_mat<K,V,V> op;
        return matrix_op<op>(op(kern,v,v));
    }
    
// ----------------------------------------------------------------------------------------

}

#endif // DLIB_SVm_KERNEL_MATRIX_

