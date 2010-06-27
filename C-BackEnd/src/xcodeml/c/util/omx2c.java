/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
package xcodeml.c.util;

import xcodeml.XmException;
import xcodeml.util.XmBackEnd;

/**
 * Run XcodeML decompiler for C language.
 */
public class omx2c
{
    public static void main(String[] args) throws XmException
    {
        System.exit(new XmBackEnd("C", "C_Back").run(args));
    }
}
