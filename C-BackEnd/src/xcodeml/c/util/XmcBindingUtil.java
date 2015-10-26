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
package xcodeml.c.util;

import xcodeml.XmException;
//import xcodeml.c.binding.gen.XbcLonglongConstant;
import xcodeml.c.decompile.XcConstObj;
import xcodeml.c.type.XcBaseTypeEnum;
import xcodeml.util.XmBindingException;
import xcodeml.util.XmStringUtil;

public class XmcBindingUtil
{
    // public static XcConstObj.LongLongConst createLongLongConst(XbcLonglongConstant visitable)
    // {
    //     String text = XmStringUtil.trim(visitable.getContent());
    //     if(text == null)
    //         throw new XmBindingException(visitable, "invalid constant value");
    //     String[] values = text.split(" ");
    //     if(values.length != 2)
    //         throw new XmBindingException(visitable, "invalid constant value");

    //     XcBaseTypeEnum btEnum;
    //     String typeId = XmStringUtil.trim(visitable.getType());
    //     if(typeId == null)
    //         btEnum = XcBaseTypeEnum.LONGLONG;
    //     else
    //         btEnum = XcBaseTypeEnum.getByXcode(typeId);

    //     if(btEnum == null)
    //         throw new XmBindingException(visitable, "invalid type '" + typeId + "' as long long constant");
        
    //     XcConstObj.LongLongConst obj;

    //     try {
    //         obj = new XcConstObj.LongLongConst(values[0], values[1], btEnum);
    //     } catch(XmException e) {
    //         throw new XmBindingException(visitable, e.getMessage());
    //     }
        
    //     return obj;
    // }

    public static XcConstObj.LongLongConst createLongLongConst(String valuesText,
							       String typeId) {
      String[] values = XmStringUtil.trim(valuesText).split(" ");
      if (values.length != 2)
	return null;

      XcBaseTypeEnum btEnum;
      if (typeId == null)
	btEnum = XcBaseTypeEnum.LONGLONG;
      else
	btEnum = XcBaseTypeEnum.getByXcode(typeId);

      if (btEnum == null)
	return null;

      XcConstObj.LongLongConst obj;

      try {
	obj = new XcConstObj.LongLongConst(values[0], values[1], btEnum);
      } catch(XmException e) {
	return null;
      }
      return obj;
    }
}
