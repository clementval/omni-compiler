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
package xcodeml.c.type;

import java.util.Set;

//import xcodeml.c.binding.gen.IRVisitable;

/**
 * Implements the interface allows type objects to evaluate not in typeTable,
 * but first appeared in symbols/globalSymbols.
 */
public interface XcLazyEvalType
{
    /**
     * notify whether this {type, ident} is
     * needed to evaluate lazy.
     * (i.e. bindingS is not evaluated.
     *
     * @return true if type need to be lazy evaluated.
     */
    public boolean isLazyEvalType();

    /**
     * Sets whether is type need to be lazy evaluated.
     *
     * @param enable whether is type need to be lazy evaluated.
     */
    public void setIsLazyEvalType(boolean enable);

    /** 
     * return xcodeml bindings which is not evaluated.
     * objects which translated from these bindings 
     * must be child of this {type, ident}.
     *
     * @return xcodeml bindings which is not evaluated.
     */
    // public IRVisitable[] getLazyBindings();

    /**
     * Sets xcodeml bindings need to be evaluated after.
     *
     * @param xcodeml bindings.
     */
    // public void setLazyBindings(IRVisitable[] bindings);

    /** 
     * return xcodeml DOM nodes which is not evaluated.
     * objects which translated from these bindings 
     * must be child of this {type, ident}.
     *
     * @return xcodeml DOM nodes which is not evaluated.
     */
    public org.w3c.dom.Node[] getLazyBindingNodes();

    /**
     * Sets xcodeml DOM nodes need to be evaluated after.
     *
     * @param xcodeml DOM nodes.
     */
    public void setLazyBindings(org.w3c.dom.Node[] nodes);

    /**
     * Gets symbol name of variables which is used to define type.
     *
     * @return name of variables.
     */
    public Set<String> getDependVar();
}
