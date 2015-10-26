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

import java.io.PrintWriter;
import java.io.Reader;
import java.io.StringReader;
import java.io.Writer;

import javax.xml.transform.OutputKeys;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;

import xcodeml.XmException;
import xcodeml.XmObj;

public class XmUtil
{
    /**
     * Format xml text to indented one.
     * 
     * @param indentSpaces
     *      number of indent spaces
     * @param reader
     *      input reader
     * @param writer
     *      output writer
     */
    public static void transformToIndentedXml(int indentSpaces, Reader reader, Writer writer)
        throws XmException
    {
        Transformer transformer = null;
        try {
            transformer = TransformerFactory.newInstance().newTransformer();
        } catch(TransformerConfigurationException e) {
            throw new XmException(e);
        }
       
        transformer.setOutputProperty(OutputKeys.METHOD, "xml");
        
        try {
            transformer.transform(new StreamSource(reader), new StreamResult(writer));
        } catch(TransformerException e) {
            throw new XmException(e);
        }
    }

    /**
     * Print XmObj as indented xml to stdout, for debugging.
     * 
     * @param indentSpaces
     *      number of indent spaces
     * @param xmobj
     *      XcodeML object
     */
    public static void printIdentedXml(int indentSpaces, XmObj xmobj) throws XmException
    {
        StringBuffer buf = new StringBuffer();
        xmobj.makeTextElement(buf);
        StringReader reader = new StringReader(buf.toString());
        buf = null;
        PrintWriter writer = new PrintWriter(System.out);
        
        transformToIndentedXml(indentSpaces, reader, writer);
    }
}
