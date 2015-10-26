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
/**
 * \file c-error.h
 * defines error message resources
 */

#ifndef C_ERROR_H
#define C_ERROR_H

#define CERR_001 "E001: syntax error"
#define CERR_002 "E002: unterminated comment"
#define CERR_003 "E003: label at end of compound statement"
#define CERR_004 "E004: duplicate '%s'"
#define CERR_005 "E005: too many type specifiers"
#define CERR_006 "E006: too many data types"
#define CERR_007 "E007: invalid 'signed' or 'unsigned'"
#define CERR_008 "E008: invalid type specifier"
#define CERR_009 "E009: invalid type qualifier"
#define CERR_010 "E010: invalid type qualifier for array length"
#define CERR_011 "E011: multiple parameters of same name"
#define CERR_012 "E012: no such parameter '%s'"
#define CERR_013 "E013: multiple parameters of same name"
#define CERR_014 "E014: expected declaration specifiers"
#define CERR_015 "E015: division by zero"
#define CERR_016 "E016: invalid cast expression"
#define CERR_017 "E017: value for '%s' is not integer constant"
#define CERR_018 "E018: %s '%s' declared inside parameter list"
#define CERR_019 "E019: no typename is specified"
#define CERR_020 "E020: invalid data definition"
#define CERR_021 "E021: unknown type '%s' is specified"
#define CERR_022 "E022: unknown type is specified"
#define CERR_023 "E023: '%s' is not declared"
#define CERR_024 "E024: '%s' is not global variable or function parameter"
#define CERR_025 "E025: label '%s' is used but not defined"
#define CERR_026 "E026: case label is not constant value"
#define CERR_027 "E027: empty range specified"
#define CERR_028 "E028: '%s' has incomplete type"
#define CERR_029 "E029: '%s' has initializer but incomplete type"
#define CERR_030 "E030: redfinition of symbol '%s'"
#define CERR_031 "E031: previous declaration of '%s' was here"
#define CERR_032 "E032: conflicting type qualifiers for '%s'"
#define CERR_033 "E033: conflicting array length for '%s'"
#define CERR_034 "E034: conflicting parameters for '%s'"
#define CERR_035 "E035: conflicting return type for '%s'"
#define CERR_036 "E036: conflicting types for '%s'"
#define CERR_037 "E037: used array designator for non-array"
#define CERR_038 "E038: used member designator for non-struct or non-union"
#define CERR_039 "E039: '%s' is not a member"
#define CERR_040 "E040: symbol '%s' is not defined"
#define CERR_041 "E041: cannot resolve type of symbol '%s'"
#define CERR_042 "E042: invalid operands to operator '%s'"
#define CERR_043 "E043: assignment of read-only variable '%s'"
#define CERR_044 "E044: assignment of read-only location"
#define CERR_045 "E045: invalid lvalue"
#define CERR_046 "E046: incompatible types in assignment"
#define CERR_047 "E047: called object is not function"
#define CERR_048 "E048: bit field with exceeds its type"
#define CERR_049 "E049: value is neither struct nor union"
#define CERR_050 "E050: value is neither struct nor union pointer"
#define CERR_051 "E051: XcodeML does not support constant type of '%s'"
#define CERR_052 "E052: syntax error in pragma expression"
#define CERR_053 "E053: syntax error in pragma expression near '%s'"
#define CERR_054 "E054: bad comment in pragma"
#define CERR_055 "E055: unknown character '%c' in pragma"
#define CERR_056 "E056: expected '%s'"
#define CERR_057 "E057: expected '%s' after '%s'"
#define CERR_058 "E058: invalid character '%c'"
#define CERR_059 "E059: invalid character after '%s'"
#define CERR_060 "E060: symbol '%s' is not found"
#define CERR_061 "E061: integer value is out of range"
#define CERR_062 "E062: unexpected end of line in pragma"
#define CERR_063 "E063: unexpected end of line in pragma"
#define CERR_064 "E064: newline in char constant"
#define CERR_065 "E065: unknown escape sequence"
#define CERR_066 "E066: too many characters"
#define CERR_067 "E067: empty character constant"
#define CERR_068 "E068: coarray dimension is not integer constant"
#define CERR_069 "E069: no dimensions in coarray declaration"
#define CERR_070 "E070: no dimensions in coarray declaration"
#define CERR_071 "E071: expected identifer in coarray declaration"
#define CERR_072 "E072: syntax error in coarray dimension specifier"
#define CERR_073 "E073: no declarators in coarray declaration"
#define CERR_074 "E074: syntax error in pragma xmp sync image"
#define CERR_075 "E075: unknown keyword '%s' in pragma xmp"
#define CERR_076 "E076: value is neither array nor pointer"
#define CERR_077 "E077: coarray value is not array or basic type"
#define CERR_078 "E078: invalid type argument of unary '*'"
#define CERR_079 "E079: type mismatch in conditional expression"
#define CERR_080 "E080: value is not pointer"
#define CERR_081 "E081: lvalue required as unary '&' operand"
#define CERR_082 "E082: array designator is not constant value"
#define CERR_083 "E083: second array designator is not constant value"
#define CERR_084 "E084: array index in no-array initializer"
#define CERR_085 "E085: empty index range in initializer"
#define CERR_086 "E086: member designator in no-struct/no-union initializer"
#define CERR_087 "E087: unknown member '%s' in member designator"
#define CERR_088 "E088: initializer field is not constant value"
#define CERR_089 "E089: empty initializer"
#define CERR_090 "E090: excess elements in initializer"
#define CERR_091 "E091: excess elements in array initializer"
#define CERR_092 "E092: invalid lvalue for initializer"
#define CERR_093 "E093: bit field width is not an integer constant"
#define CERR_094 "E094: invalid initializer"
#define CERR_095 "E095: invalid initializer for array value"
#define CERR_096 "E096: type mismatch in initializer"
#define CERR_097 "E097: array size is not constant"
#define CERR_098 "E098: redeclaration of '%s'"
#define CERR_099 "E099: redeclaration of '%s' as different kind of symbol"
#define CERR_100 "E100: non-static declaration of '%s follows static declaration"
#define CERR_101 "E101: invalid escape sequence in character constant"
#define CERR_102 "E102: too many characters in character constant"
#define CERR_103 "E103: invalid escape sequence in character constant"
#define CERR_104 "E104: non-declarator in parameter declaration"
#define CERR_105 "E105: value is not coarray"
#define CERR_106 "E106: bit field has invalid type"
#define CERR_107 "E107: storage size of '%s' is unknown"
#define CERR_108 "E108: typedef '%s' has an initializer"
#define CERR_109 "E109: function type is invaild at member '%s'"
#define CERR_110 "E110: function '%s' is initialized like a variable" 
#define CERR_111 "E111: '%s' is initialized and declared extern"
#define CERR_112 "E112: functions array is invaild"
#define CERR_113 "E113: switch quantity not an integer"
#define CERR_114 "E114: duplicate case value"
#define CERR_115 "E115: duplicated default label"
#define CERR_116 "E116: variable has initializer but incomplete type"
#define CERR_117 "E117: break statement not within loop or switch"
#define CERR_118 "E118: array designator is nagative"
#define CERR_119 "E119: array size is negative"
#define CERR_120 "E120: array size is too large"
#define CERR_121 "E121: integer constant exceeds range of '%s'"
#define CERR_122 "E122: floating constant exceeds range of '%s'"
#define CERR_123 "E123: illegal function return type"
#define CERR_124 "E124: illegal cast operation"
#define CERR_125 "E125: continue statement not within loop"
#define CERR_126 "E126: illegal logical expression"
#define CERR_127 "E127: illegal logical expression for operator '%s'"
#define CERR_128 "E128: incompatible types in return"
#define CERR_129 "E129: invalid applicaton of 'sizeof' to incomplete type"
#define CERR_130 "E130: return value of unknown size"
#define CERR_131 "E131: too few arguments to function '%s'"
#define CERR_132 "E132: too many arguments to function '%s'"
#define CERR_133 "E133: incompatible type in argument %d of '%s'"
#define CERR_134 "E134: abbreviated subarray upper bound for incomplete array type"
#define CERR_135 "E135: subarray assignment used as expression"
#define CERR_136 "E136: value is not array"
#define CERR_137 
#define CERR_138 
#define CERR_139 
#define CERR_140 
#define CERR_141 
#define CERR_142 
#define CERR_143 
#define CERR_144 
#define CERR_145 
#define CERR_146 
#define CERR_147 
#define CERR_148 
#define CERR_149 

#define CERR_500 "E500: unknown option %s\n"
#define CERR_501 "E501: failed to open input file"
#define CERR_502 "E502: failed to open output file"
#define CERR_503 "E503: needs argument after %s\n"
#define CERR_504 "E504: too many input files '%s'"
#define CERR_505 "E505: needs value after %s=\n"
#define CERR_506 "E506: illegal value for %s*"
#define CERR_507 "E507: illegal type name for %s*"
#define CERR_508 
#define CERR_509 

#define CWRN_001 "W001: no type or storage class"
#define CWRN_002 "W002: data definition has no type or storage class"
#define CWRN_003 "W003: implicit declaration of function '%s'"
#define CWRN_004 "W004: overwriting initialization in same location"
#define CWRN_005 "W005: initialization makes integer from pointer without a cast"
#define CWRN_006 "W006: initialization from incompatible pointer type"
#define CWRN_007 "W007: \\x must follow hex digit"
#define CWRN_008 "W008: cannot reduce bit field width, so the size is assumed as its type size"
#define CWRN_009 "W009: declaration of '%s' hides a parameter"
#define CWRN_010 "W010: missing '(' after '#pragma pack' - ignored"
#define CWRN_011 "W011: no semicolon at end of struct/union"
#define CWRN_012 "W012: '%s' attribute directive ignored"
#define CWRN_013 "W013: default label not within a switch statement"
#define CWRN_014 "W014: case label not within a switch statement"
#define CWRN_015 "W015: cast to pointer from integer of different size"
#define CWRN_016 "W016: cast to integer from pointer of different size"
#define CWRN_017 "W017: return with a value, in function returning void"
#define CWRN_018 "W018: return with no value, in function returning non-void"
#define CWRN_019 "W019: comparison between pointer and integer"
#define CWRN_020 "W020: comparison between incompatible pointer type"
#define CWRN_021 "W021: passing argument %d of '%s' makes pointer from integer without a cast"
#define CWRN_022 "W022: passing argument %d of '%s' makes integer from pointer without a cast"
#define CWRN_023 "W023: incompatible pointer type in argument %d of '%s'"
#define CWRN_024 "W024: initialization makes pointer from integer without a cast"
#define CWRN_025 "W025: argument for '#pragma pack' is not zero or positive integer constant - ignore"
#define CWRN_026 
#define CWRN_027 
#define CWRN_028 
#define CWRN_029 
#define CWRN_030 


#define CFTL_001 "F001: declarator of '%s' is not found"
#define CFTL_002 "F002: cannot resolve type of expression"
#define CFTL_003 "F003: too long string in pragma"
#define CFTL_004 "F004: too long string"
#define CFTL_005 "F005: symbol table was corrupted"
#define CFTL_006 "F006: non-parameter in paramter list"
#define CFTL_007 "F007: not output gcc attribute '%s'"
#define CFTL_008 "F008: case value constant check is illegal"
#define CFTL_009 
#define CFTL_010 

#endif // C_ERROR_H

