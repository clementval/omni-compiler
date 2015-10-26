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
        printf("#include \"F-front.h\"\n");
        printf("/* generated from C-exprcode.def */\n");
        printf("struct expr_code_info expr_code_info[] = {\n");
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
        if(NF == 2) 
                printf("/* %d */\t{\t'%s',\t\"%s\",\tNULL},\n",i++,$1,$2);
        else if(NF == 3) 
                printf("/* %d */\t{\t'%s',\t\"%s\",\t\"%s\"},\n",i++,$1,$2,$3);
}

END {
        printf("};\n");
        printf("/* END */\n");
}

