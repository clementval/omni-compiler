/* 
 * $TSUKUBA_Release: Omni Compiler Version 0.9.1 $
 * $TSUKUBA_Copyright:
 *  Copyright (C) 2010-2014 University of Tsukuba, 
 *  	      2012-2014  University of Tsukuba and Riken AICS
 *  
 *  This software is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 published by the Free Software Foundation.
 *  
 *  Please check the Copyright and License information in the files named
 *  COPYRIGHT and LICENSE under the top  directory of the Omni Compiler
 *  Software release kit.
 *  
 *  * The specification of XcalableMP has been designed by the XcalableMP
 *    Specification Working Group (http://www.xcalablemp.org/).
 *  
 *  * The development of this software was partially supported by "Seamless and
 *    Highly-productive Parallel Programming Environment for
 *    High-performance computing" project funded by Ministry of Education,
 *    Culture, Sports, Science and Technology, Japan.
 *  $
 */
package xcodeml.util;

import xcodeml.XmLanguage;

/**
 * Decompile option.
 */
public class XmOption
{
    public static final int COMP_VENDOR_GNU = 'G';
    public static final int COMP_VENDOR_INTEL = 'I';

    /** if suppress to write line directives */
    private static boolean _suppressLineDirective = false;

    /** if compiling Xcalable MP is enabled */
    private static boolean _xcalableMP = false;
    private static boolean _xcalableMPthreads = false;
    private static boolean _xcalableMPGPU = false;
    private static boolean _xcalableMPasync = false;

    private static boolean _tlog = false;

    /** if compiling OpenMP is enabled */
    private static boolean _openMP = false;

    /** if compiling coarray is enabled */
    private static boolean _coarray = false;

    /** if debug output is enabled */
    private static boolean _debugOutput = false;

    /** target language ID */
    private static XmLanguage _language = XmLanguage.C;
    
    /** if transforming Fortran IO statement as atomic operation */
    private static boolean _isAtomicIO = false;

    /** backend compiler vendor */
    private static int _compilerVendor = COMP_VENDOR_GNU;
    
    private XmOption()
    {
    }

    /**
     * Sets compiler to or not to suppress to write line directives.
     *
     * @param enable true then compiler suppress to write line directives.
     */
    public static void setIsSuppressLineDirective(boolean enable)
    {
        _suppressLineDirective = enable;
    }

    /**
     * Checks does decompiler suppress line directives.
     *
     * @return true if compiler suppress to write line directives.
     */
    public static boolean isSuppressLineDirective()
    {
        return _suppressLineDirective;
    }

    /**
     * Sets compiler to or not to translate XcalableMP directive.
     *
     * @param enable true then translate XcalableMP directive.
     */
    public static void setIsXcalableMP(boolean enable)
    {
        _xcalableMP = enable;
    }

    /**
     * Checks does compiler translate XcalableMP directive.
     *
     * @return true if compiler translate XcalableMP directive.
     */
    public static boolean isXcalableMP()
    {
        return _xcalableMP;
    }

    /**
     * Sets compiler to or not to translate XcalableMP-threads directive.
     */
    public static void setIsXcalableMPthreads(boolean enable)
    {
        _xcalableMPthreads = enable;
    }

    /**
     * Checks does compiler translate XcalableMP-threads directive.
     */
    public static boolean isXcalableMPthreads()
    {
        return _xcalableMPthreads;
    }

    /**
     * Sets compiler to or not to translate XcalableMP-GPU directive.
     */
    public static void setIsXcalableMPGPU(boolean enable)
    {
        _xcalableMPGPU = enable;
    }

    /**
     * Checks does compiler translate XcalableMP-GPU directive.
     */
    public static boolean isXcalableMPGPU()
    {
        return _xcalableMPGPU;
    }

    /**
     * Sets whether the compiler supports asynchronous communications or not.
     */
    public static void setIsAsync(boolean enable)
    {
        _xcalableMPasync = enable;
    }

    /**
     * Checks if the compiler supports asynchronous communications.
     */
    public static boolean isAsync()
    {
        return _xcalableMPasync;
    }

    /**
     * Sets compiler to or not to use tlog for MPI.
     */
    public static void setTlogMPIisEnable(boolean enable)
    {
        _tlog = enable;
    }

    /**
     * Checks does compiler use tlog for MPI.
     */
    public static boolean tlogMPIisEnable()
    {
        return _tlog;
    }

    /**
     * Sets compiler to or not to translate OpenMP directive.
     *
     * @param enable true then translate OpenMP directive.
     */
    public static void setIsOpenMP(boolean enable)
    {
        _openMP = enable;
    }

    /**
     * Checks does compiler translate OpenMP directive.
     *
     * @return true if compiler translate OpenMP directive.
     */
    public static boolean isOpenMP()
    {
        return _openMP;
    }

    /**
     * Sets compiler to or not to translate coarrays
     *
     * @param enable true then translate coarrays.
     */
    public static void setIsCoarray(boolean enable)
    {
        _coarray = enable;
    }

    /**
     * Checks does compiler translate coarrays.
     *
     * @return true if compiler translate coarrays.
     */
    public static boolean isCoarray()
    {
        return _coarray;
    }

    /**
     * Return true if debug output enabled.
     */
    public static boolean isDebugOutput()
    {
        return _debugOutput;
    }

    /**
     * Set debug output.
     */
    public static void setDebugOutput(boolean enable)
    {
        _debugOutput = enable;
    }

    /**
     * Set language
     */
    public static void setLanguage(XmLanguage lang)
    {
        _language = lang;
    }
    
    /**
     * Get language
     */
    public static XmLanguage getLanguage()
    {
        return _language;
    }

    /**
     * Return if the language is C
     */
    public static boolean isLanguageC()
    {
        return _language.equals(XmLanguage.C);
    }

    /**
     * Return if the language is Fortran
     */
    public static boolean isLanguageF()
    {
        return _language.equals(XmLanguage.F);
    }

    /**
     * Return compiler vendor constant. (COMP_VENDOR_*)
     */
    public static int getCompilerVendor()
    {
        return _compilerVendor;
    }

    /**
     * Set compiler vendor constant. (COMP_VENDOR_*)
     */
    public static void setCompilerVendor(int vendor)
    {
        _compilerVendor = vendor;
    }

    /**
     * Get if or not IO statements are transformed to atomic operation.
     */
    public static boolean isAtomicIO()
    {
        return _isAtomicIO || _compilerVendor == COMP_VENDOR_INTEL;
    }

    /**
     * Set if or not IO statements are transformed to atomic operation.
     */
    public static void setIsAtomicIO(boolean atomicIO)
    {
        _isAtomicIO = atomicIO;
    }
}
