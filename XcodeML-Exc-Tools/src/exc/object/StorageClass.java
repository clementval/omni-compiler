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
package exc.object;

//import xcodeml.c.binding.gen.XbcId;
//import xcodeml.f.binding.gen.XbfId;
import xcodeml.util.XmLog;

/**
 * Storage Class
 */
public enum StorageClass
{
    SNULL           (null),                         /* undefined */
    // C
    AUTO            ("auto"),            /* auto variable */
    PARAM           ("param"),           /* paramter */
    EXTERN          ("extern"),          /* extern variable */
    EXTDEF          ("extern_def"),      /* external defition */
    STATIC          ("static"),          /* static variable */
    REGISTER        ("register"),        /* register variable */
    LABEL           ("label"),           /* label */
    ULABEL          ("_label"),          /* undefined label, (temporary) */
    TAGNAME         ("tagname"),         /* tag name for struct/union/enum */
    MOE             ("moe"),             /* member of enum */
    TYPEDEF_NAME    ("typedef_name"),    /* typedef name */
    REG             ("_reg"),            /* register, temporary variable */
    MEMBER          ("_member"),         /* C++ class member */
    GCC_LABEL       ("gccLabel"),        /* gcc block scope label */
    
    // Fortran
    FLOCAL          ("flocal"),          /* local variable */
    FSAVE           ("fsave"),           /* module var or var which has save attribute */
    FCOMMON         ("fcommon"),         /* common variable */
    FPARAM          ("fparam"),          /* dummy argument */
    FFUNC           ("ffunc"),           /* func/sub/program name */
    FTYPE_NAME      ("ftype_name"),      /* type name */
    FCOMMON_NAME    ("fcommon_name"),    /* common name */
    FNAMELIST_NAME  ("fnamelist_name"),  /* namelist name */
    ;

    private String xcodeStr;

    private StorageClass(String xcodeStr)
    {
        this.xcodeStr = xcodeStr;
    }

    public String toXcodeString()
    {
        return xcodeStr;
    }
    
    public boolean canBeAddressed()
    {
        switch(this) {
        case PARAM:
        case AUTO:
        case EXTERN:
        case EXTDEF:
        case STATIC:
            return true;
        }
        
        return false;
    }
    
    public boolean isVarOrFunc()
    {
        switch(this) {
        case PARAM:
        case AUTO:
        case EXTERN:
        case EXTDEF:
        case STATIC:
        case REGISTER:
        case FLOCAL:
        case FSAVE:
        case FCOMMON:
        case FPARAM:
        case FFUNC:
            return true;
        }
        
        return false;
    }
    
    public boolean isBSS()
    {
        switch(this) {
        case EXTERN:
        case EXTDEF:
        case STATIC:
        case FCOMMON:
        case FSAVE:
            return true;
        }
        return false;
    }
    
    public boolean isFuncParam()
    {
        switch(this) {
        case PARAM:
        case FPARAM:
            return true;
        }
        return false;
    }
    
    public static StorageClass get(String s)
    {
        if(s == null)
            return null;
        
        for(StorageClass stg : values()) {
            if(s.equalsIgnoreCase(stg.xcodeStr)) {
                return stg;
            }
        }
        
        XmLog.fatal("unkown class '" + s + "'");
        return null;
    }
}
