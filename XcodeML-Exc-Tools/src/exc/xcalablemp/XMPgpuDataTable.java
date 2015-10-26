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

package exc.xcalablemp;

import exc.block.*;
import java.util.HashMap;

public class XMPgpuDataTable {
  public static String PROP = "XMP_GPU_DATA_TABLE";

  private HashMap<String, XMPgpuData> _XMPgpuDataTable;

  public XMPgpuDataTable() {
    _XMPgpuDataTable = new HashMap<String, XMPgpuData>();
  }

  public void putXMPgpuData(XMPgpuData gpuData) {
    _XMPgpuDataTable.put(gpuData.getName(), gpuData);
  }

  public XMPgpuData getXMPgpuData(String name) {
    return _XMPgpuDataTable.get(name);
  }

  public static XMPgpuData findXMPgpuData(String varName, Block block) {
    if (block == null) {
      return null;
    }

    for (Block b = block; b != null; b = b.getParentBlock()) {
      XMPgpuDataTable gpuDataTable = (XMPgpuDataTable)b.getProp(XMPgpuDataTable.PROP);
      if (gpuDataTable != null) {
        XMPgpuData gpuData = gpuDataTable.getXMPgpuData(varName);
        if (gpuData != null) {
          return gpuData;
        }
      }
    }

    return null;
  }
}
