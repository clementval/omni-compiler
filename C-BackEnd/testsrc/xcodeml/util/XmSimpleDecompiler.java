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

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.ArrayList;
import java.util.List;

import xcodeml.XmException;
import xcodeml.c.binding.gen.XbcXcodeProgram;
import xcodeml.c.decompile.XcBindingVisitor;
import xcodeml.c.decompile.XcProgramObj;
import xcodeml.c.util.XmcValidator;
import xcodeml.c.util.XmcWriter;

public class XmSimpleDecompiler
{
    private Reader _xmlInput;
    
    private XmcWriter _writer;
    
    private boolean _bufferedOutput;
    
    private boolean _debug;
    
    private boolean _addXml;
    
    private void _error(String s)
    {
        System.err.println(s);
    }
    
    private void _error(Exception e, String s)
    {
        if(_debug) {
            e.printStackTrace();
        } else {
            System.err.println(s + " : " + e.getMessage());
        }
    }
    
    private void _usage()
    {
        _error("usage : XmSimpleDecompiler <XML_INPUT_FILE> <-o C_OUTPUT_FILE> <-d>");
        _error("  XML_INPUT_FILE ... XcodeML file for input. If not specified, using stdin.");
        _error("  C_OUTPUT_FILE ... C source file for output. If not specified, using stdout.");
        _error("  -x ... Add input XcodeML to C source file as comments.");
        _error("  -d ... Debug mode. Output detail error information.");
    }
    
    private boolean _getOpt(String[] args)
    {
        String inputFilePath = null;
        String outputFilePath = null;
        
        for(int i = 0; i < args.length; ++i) {
            String arg = args[i];
            String narg = (i < args.length - 1) ? args[i + 1] : null;
            
            if(arg.startsWith("-")) {
                if(arg.equals("-o")) {
                    if(narg == null) {
                        _error("needs argument after -o.");
                        return false;
                    }
                    outputFilePath = narg;
                    ++i;
                } else if(arg.equals("-x")) {
                    _addXml = true;
                } else if(arg.equals("-d")) {
                    _debug = true;
                } else if(arg.equals("-h")) {
                    _usage();
                    System.exit(1);
                } else {
                    _error("Unknown option " + arg + ".");
                    return false;
                }
            } else if(inputFilePath == null) {
                inputFilePath = arg;
            } else {
                _error("Too many input files.");
                return false;
            }
        }

        try {
            if(inputFilePath == null) {
                _xmlInput = new BufferedReader(new InputStreamReader(System.in));
            } else {
                _xmlInput = new BufferedReader(new FileReader(inputFilePath));
            }
        } catch(IOException e) {
            _error("Cannot open input file (" + e.getMessage() + ").");
            return false;
        }

        try {
            if(outputFilePath == null) {
                // useful for debug
                _writer = new XmcWriter();
                _bufferedOutput = true;
                _writer.setIsDebugMode(_debug);
            } else {
                _writer = new XmcWriter(new BufferedWriter(new FileWriter(outputFilePath)));
                _writer.setIsDebugMode(_debug);
            }
        } catch(IOException e) {
            _error("Cannot open output file (" + e.getMessage() + ").");
            return false;
        }
        return true;
    }

    private int _run(String[] args) throws XmException
    {
        if(_getOpt(args) == false)
            return 1;
        
        List<String> errorList = new ArrayList<String>();

        try {
            XmValidator validator = new XmcValidator();
            XbcXcodeProgram xprog = new XbcXcodeProgram();
            
            if(validator.read(_xmlInput, xprog, errorList) == false) {
                for(String error : errorList)
                    _error("Error at reading XML file: " + error);
                return 1;
            }
            
            if(_addXml) {
                _writer.println("/* -----------");
                _writer.println(xprog.makeTextDocument());
                _writer.println("----------- */");
            }
    
            XcProgramObj prog = null;
            
            try {
                prog = XcBindingVisitor.createXcProgramObj(xprog);
            } catch(XmBindingException e) {
                _error(e, "Error at decompiling:");
                _error("  location: " + e.getElementDesc());
                return 1;
            }
            
            try {
                prog.writeTo(_writer);
            } catch (XmException e) {
                _error("Failed to write output (" + e.getMessage() + ").");
                return 1;
            }
            
            if(_bufferedOutput) {
                System.out.println(_writer.toString());
            }
            
            return 0;
            
        } finally {
            if(_xmlInput != null)
                try { _xmlInput.close(); } catch(Exception e) {}
            if(_writer != null)
                try { _writer.close(); } catch(Exception e) {}
        }
    }
    
    public static void main(String[] args) throws XmException
    {
        System.exit(new XmSimpleDecompiler()._run(args));
    }
}
