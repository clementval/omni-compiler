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

import org.w3c.dom.*;
import java.util.Set;

/**
 * Collector of variable references.
 */
public class XmcVarCollector {
    public XmcVarCollector(Set<String> variables) {
        this.variables = variables;
    }

    public void collectVars(Node n){
        String nodeName = n.getNodeName();      
        Boolean isVarNode = nodeName.equals("Var")
                || nodeName.equals("varAddr")
                || nodeName.equals("funcAddr")
                || nodeName.equals("memberRef");

        NodeList cnList = n.getChildNodes();
        for(int i=0; i<cnList.getLength(); i++){
            Node cn = cnList.item(i);
            if(isVarNode && cn.getNodeType() == Node.TEXT_NODE){
                variables.add(cn.getNodeValue());
            }else{
                collectVars(cn);
            }
        }
    }

    private Set<String> variables;
}
