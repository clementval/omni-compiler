# $TSUKUBA_Release: Omni Compiler Version 0.9.1 $
# $TSUKUBA_Copyright:
#  Copyright (C) 2010-2014 University of Tsukuba, 
#  	      2012-2014  University of Tsukuba and Riken AICS
#  
#  This software is free software; you can redistribute it and/or modify
#  it under the terms of the GNU Lesser General Public License version
#  2.1 published by the Free Software Foundation.
#  
#  Please check the Copyright and License information in the files named
#  COPYRIGHT and LICENSE under the top  directory of the Omni Compiler
#  Software release kit.
#  
#  * The specification of XcalableMP has been designed by the XcalableMP
#    Specification Working Group (http://www.xcalablemp.org/).
#  
#  * The development of this software was partially supported by "Seamless and
#    Highly-productive Parallel Programming Environment for
#    High-performance computing" project funded by Ministry of Education,
#    Culture, Sports, Science and Technology, Japan.
#  $
BEGIN{
        printf("/* generated from C-exprcode.def */\n");
        printf("#ifndef _C_EXPRCODE_H_\n#define _C_EXPRCODE_H_\n");
        printf("enum expr_code {\n");
        i = 0;
}

{
        if(NF == 0){
                next;
        }
        ## skip comment 
        if($1 == "#"){
                next;
        }
        # generate entry
        printf("\t%s = %d,\n", $2,i++);
}

END {
        printf("\tEXPR_CODE_END\n};\n");
        printf("/* END */\n");
        printf("#define MAX_CODE %d\n", i);
        printf("#endif /* _C_EXPRCODE_H_ */\n");
}

