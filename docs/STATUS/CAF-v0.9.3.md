                                                                      2016.01.25
                                                                      Ver 0.9.3

              Coarray Fortran features and the current restrictions

1. General
  Coarray features included in Fortran2008 standard were partially implemented
  implemented in the XcalableMP/Fortran compiler. The specifications are major
  part of description of the article[1]. In addition, some intrinsic procedures
  defined in Fortran2015 standard were supported, which are co_broadcast, 
  co_sum, co_max and co_min described in the technical specification (TS)[2].

  Currlentry, there are a few restrictions in XcalableMP/Fortran compiler to use
  the coarray features:
    * To use any coarray features, built-in header file 'xmp_coarray.h' must be 
      included at the top of each program unit.
    * Coarray features cannot be used together with XcalableMP directives.

  [1] John Reid, JKR Associates, UK. Coarrays in the next Fortran Standard.
      ISO/IEC JTC1/SC22/WG5 N1824, April 21, 2010.
  [2] ISO/IEC TS 18508:2015, Information technology -- Additional Parallel 
      Features in Fortran, Technical Specification, December 1, 2015.

2. Declaration
  Either static or allocatable coarray data objects can be used in the program. 
  Use- and host-associations are available but common- or equivalence-
  association are not allowed.
  Current restrictions against Fortran2008 coarray features:
    * Rank (number of dimensions) of an array may not be more than 7.
    * A coarray cannot be of a derived type nor be a structure component.
    * A coarray cannot be of quadruple precision, i.e., 16-byte real or 32-byte 
      complex.
    * Interface block cannot contains any specification of coarrays. To describe
      explicit interface, host-assocication (using internal procedure) can be 
      used instead.
      
2.1  Static Coarray
  E.g.
      real(8) :: a(100,100)[*], s(1000)[2,2,*]
      integer, save :: n[*], m(3)[4,*]
  The data object is allocated previously before the execution of the user 
  program.  A recursive procedure cannot have a non-allocatable coarray without 
  SAVE attribute.
  Current restrictions against Fortran2008 coarray features:
    * Each lower/upper bound of the shape must be such a simple expression that 
      is an integer constant literal, a simple integer constant expression, or a 
      reference of an integer named constant defined with a simple integer 
      constant expression.
    * A coarray cannot be initialized with initialization or with a DATA 
      statement.
    
2.2  Allocatable Coarray
  E.g.
      real(8), allocatable :: a(:,:)[:], s(:)[:]
      integer, allocatable, save :: n[:], m(:)[:,:]
  The data object is allocated with an ALLOCATE statement as follows:
      allocate ( a(100,100)[*], s(1000)[2,2,*] )
  The allocated coarray is deallocated with an explicit DEALLOCATE statement or 
  with an automatic deallocation at the end of the scope of the name unless it 
  has SAVE attribute.
  Current restrictions against fortran2008 coarray features:
    * A scalar coarray cannot be allocatable.
    * An allocatable coarray as a dummy argument cannot be allocated or 
      deallocated.
    
3. Inter-image communication
  For the performance of communication, it is recommended to use array 
  assignment statements and array expressions of coindexed objects as follows:
      a(:) = b(i,:)[k1] * c(:,j)[k2]    !! getting data from images k1 and k2
      if (this_image(1))  d[k3] = e     !! putting data d on k3 from e
  
4. Image control statements
  SYNC ALL, SYNC MEMORY and SYNC IMAGES statements are available.
  Current restrictions against Fortran2008 coarray features:
    * LOCK, UNLOCK, CRITICAL and END CRITICAL statements are not supported.
    * STAT= and ERRMSG= specifiers of image control statements are not 
      supported.
    * ERROR STOP statement is not supported.
    
5. Incrinsic Functions
  Inquire functions NUM_IMAGES, THIS_IMAGE, IMAGE_INDEX, LCOBOUND and LUBOUND
  are supported.
  Current restrictions against Fortran2008 coarray features:
    * ATOMIC_DEFINE and ATOMIC_REF subroutines are not supported.

6. Intrinsic Procedures in Fortran2015
  Intrinsic subroutines CO_BROADCAST, CO_SUM, CO_MAX and CO_MIN can be used 
  only in the following form:
    * CO_BROADCAST with two arguments SOURCE and SOURCE_IMAGE
      E.g.,  call co_broadcast(a(:), image)
    * CO_SUM, CO_MAX and CO_MIN with two arguments SOURCE and RESULT
      E.g.,  call co_max(a, amax)
  Argument SOURCE can be a coarray or a non-coarray.
