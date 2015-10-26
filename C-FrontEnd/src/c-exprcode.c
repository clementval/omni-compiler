/* This file is generated automatically by c-exprcode.pl */

#include "c-expr.h"
#include "c-exprcode.h"

const CExprCodeInfo s_CExprCodeInfos[] = {
	{ ET_UNARYOPE , "UNDEF"                          , (void*)0 },
	{ ET_TERMINAL , "CHAR_CONST"                     , (void*)0 },
	{ ET_TERMINAL , "STRING_CONST"                   , (void*)0 },
	{ ET_TERMINAL , "NUMBER_CONST"                   , (void*)0 },
	{ ET_TERMINAL , "DEFAULT_LABEL"                  , (void*)0 },
	{ ET_TERMINAL , "ELLIPSIS"                       , (void*)0 },
	{ ET_TERMINAL , "IDENT"                          , (void*)0 },
	{ ET_TERMINAL , "NULL_NODE"                      , (void*)0 },
	{ ET_LIST     , "EXT_DEFS"                       , (void*)0 },
	{ ET_LIST     , "FUNC_DEF"                       , (void*)0 },
	{ ET_BINARYOPE, "DECL"                           , (void*)0 },
	{ ET_BINARYOPE, "DATA_DEF"                       , (void*)0 },
	{ ET_UNARYOPE , "INIT"                           , (void*)0 },
	{ ET_BINARYOPE, "INITIALIZER"                    , (void*)0 },
	{ ET_LIST     , "INITIALIZERS"                   , (void*)0 },
	{ ET_LIST     , "INIT_DECL"                      , (void*)0 },
	{ ET_LIST     , "INIT_DECLS"                     , (void*)0 },
	{ ET_LIST     , "DESIGNATORS"                    , (void*)0 },
	{ ET_BINARYOPE, "ARRAY_DESIGNATOR"               , (void*)0 },
	{ ET_LIST     , "DECLARATOR"                     , (void*)0 },
	{ ET_LIST     , "STRUCT_TYPE"                    , (void*)0 },
	{ ET_LIST     , "UNION_TYPE"                     , (void*)0 },
	{ ET_LIST     , "ENUM_TYPE"                      , (void*)0 },
	{ ET_LIST     , "MEMBERS"                        , (void*)0 },
	{ ET_BINARYOPE, "MEMBER_DECL"                    , (void*)0 },
	{ ET_LIST     , "MEMBER_DECLS"                   , (void*)0 },
	{ ET_BINARYOPE, "MEMBER_DECLARATOR"              , (void*)0 },
	{ ET_LIST     , "ENUMERATORS"                    , (void*)0 },
	{ ET_LIST     , "GCC_LABEL_DECLS"                , (void*)0 },
	{ ET_BINARYOPE, "COMPOUND_LITERAL"               , (void*)0 },
	{ ET_LIST     , "PARAMS"                         , (void*)0 },
	{ ET_LIST     , "IDENTS"                         , (void*)0 },
	{ ET_LIST     , "GCC_LABEL_IDENTS"               , (void*)0 },
	{ ET_LIST     , "STMTS_AND_DECLS"                , (void*)0 },
	{ ET_LIST     , "COMP_STMT"                      , (void*)0 },
	{ ET_LIST     , "EXPRS"                          , (void*)0 },
	{ ET_UNARYOPE , "GCC_COMP_STMT_EXPR"             , (void*)0 },
	{ ET_UNARYOPE , "EXPR_STMT"                      , (void*)0 },
	{ ET_LIST     , "IF_STMT"                        , (void*)0 },
	{ ET_BINARYOPE, "WHILE_STMT"                     , (void*)0 },
	{ ET_BINARYOPE, "DO_STMT"                        , (void*)0 },
	{ ET_LIST     , "FOR_STMT"                       , (void*)0 },
	{ ET_BINARYOPE, "SWITCH_STMT"                    , (void*)0 },
	{ ET_UNARYOPE , "BREAK_STMT"                     , (void*)0 },
	{ ET_UNARYOPE , "CONTINUE_STMT"                  , (void*)0 },
	{ ET_UNARYOPE , "RETURN_STMT"                    , (void*)0 },
	{ ET_UNARYOPE , "GOTO_STMT"                      , (void*)0 },
	{ ET_BINARYOPE, "CASE_LABEL"                     , (void*)0 },
	{ ET_UNARYOPE , "LABEL"                          , (void*)0 },
	{ ET_LIST     , "LABELS"                         , (void*)0 },
	{ ET_BINARYOPE, "FUNCTION_CALL"                  , (void*)0 },
	{ ET_TERMINAL , "TYPE_DESC"                      , (void*)0 },
	{ ET_UNARYOPE , "BRACED_EXPR"                    , (void*)0 },
	{ ET_UNARYOPE , "UNARY_MINUS"                    , "-"      },
	{ ET_UNARYOPE , "BIT_NOT"                        , "~"      },
	{ ET_UNARYOPE , "POINTER_REF"                    , "*"      },
	{ ET_UNARYOPE , "ADDR_OF"                        , "&"      },
	{ ET_UNARYOPE , "PRE_INCR"                       , "++"     },
	{ ET_UNARYOPE , "PRE_DECR"                       , "--"     },
	{ ET_UNARYOPE , "LOG_NOT"                        , "!"      },
	{ ET_UNARYOPE , "SIZE_OF"                        , (void*)0 },
	{ ET_UNARYOPE , "CAST"                           , (void*)0 },
	{ ET_UNARYOPE , "POST_INCR"                      , "++"     },
	{ ET_UNARYOPE , "POST_DECR"                      , "--"     },
	{ ET_BINARYOPE, "LSHIFT"                         , "<<"     },
	{ ET_BINARYOPE, "RSHIFT"                         , ">>"     },
	{ ET_BINARYOPE, "PLUS"                           , "+"      },
	{ ET_BINARYOPE, "MINUS"                          , "-"      },
	{ ET_BINARYOPE, "MUL"                            , "*"      },
	{ ET_BINARYOPE, "DIV"                            , "/"      },
	{ ET_BINARYOPE, "MOD"                            , "%"      },
	{ ET_BINARYOPE, "ARITH_EQ"                       , "=="     },
	{ ET_BINARYOPE, "ARITH_NE"                       , "!="     },
	{ ET_BINARYOPE, "ARITH_GE"                       , ">="     },
	{ ET_BINARYOPE, "ARITH_GT"                       , ">"      },
	{ ET_BINARYOPE, "ARITH_LE"                       , "<="     },
	{ ET_BINARYOPE, "ARITH_LT"                       , "<"      },
	{ ET_BINARYOPE, "LOG_AND"                        , "&&"     },
	{ ET_BINARYOPE, "LOG_OR"                         , "||"     },
	{ ET_BINARYOPE, "BIT_AND"                        , "&"      },
	{ ET_BINARYOPE, "BIT_OR"                         , "|"      },
	{ ET_BINARYOPE, "BIT_XOR"                        , "^"      },
	{ ET_BINARYOPE, "ASSIGN"                         , "="      },
	{ ET_BINARYOPE, "ASSIGN_PLUS"                    , "+="     },
	{ ET_BINARYOPE, "ASSIGN_MINUS"                   , "-="     },
	{ ET_BINARYOPE, "ASSIGN_MUL"                     , "*="     },
	{ ET_BINARYOPE, "ASSIGN_DIV"                     , "/="     },
	{ ET_BINARYOPE, "ASSIGN_MOD"                     , "%="     },
	{ ET_BINARYOPE, "ASSIGN_LSHIFT"                  , "<<="    },
	{ ET_BINARYOPE, "ASSIGN_RSHIFT"                  , ">>="    },
	{ ET_BINARYOPE, "ASSIGN_BIT_AND"                 , "&="     },
	{ ET_BINARYOPE, "ASSIGN_BIT_OR"                  , "|="     },
	{ ET_BINARYOPE, "ASSIGN_BIT_XOR"                 , "^="     },
	{ ET_LIST     , "CONDEXPR"                       , "?"      },
	{ ET_BINARYOPE, "POINTS_AT"                      , "->"     },
	{ ET_BINARYOPE, "ARRAY_REF"                      , "[]"     },
	{ ET_LIST     , "ARRAY_DIMENSION"                , (void*)0 },
	{ ET_BINARYOPE, "MEMBER_REF"                     , "."      },
	{ ET_UNARYOPE , "FLEXIBLE_STAR"                  , (void*)0 },
	{ ET_LIST     , "XMP_COARRAY_DECLARATION"        , (void*)0 },
	{ ET_LIST     , "XMP_COARRAY_DECLARATIONS"       , (void*)0 },
	{ ET_LIST     , "XMP_COARRAY_DIM_DEFS"           , (void*)0 },
	{ ET_LIST     , "XMP_COARRAY_DIMENSIONS"         , (void*)0 },
	{ ET_BINARYOPE, "XMP_COARRAY_REF"                , (void*)0 },
	{ ET_TERMINAL , "XMP_CRITICAL"                   , (void*)0 },
	{ ET_TERMINAL , "GCC_EXTENSION"                  , (void*)0 },
	{ ET_UNARYOPE , "GCC_LABEL_ADDR"                 , (void*)0 },
	{ ET_UNARYOPE , "GCC_ALIGN_OF"                   , (void*)0 },
	{ ET_UNARYOPE , "GCC_TYPEOF"                     , (void*)0 },
	{ ET_UNARYOPE , "GCC_REALPART"                   , (void*)0 },
	{ ET_UNARYOPE , "GCC_IMAGPART"                   , (void*)0 },
	{ ET_BINARYOPE, "GCC_BLTIN_VA_ARG"               , (void*)0 },
	{ ET_BINARYOPE, "GCC_BLTIN_OFFSET_OF"            , (void*)0 },
	{ ET_BINARYOPE, "GCC_BLTIN_TYPES_COMPATIBLE_P"   , (void*)0 },
	{ ET_BINARYOPE, "GCC_OFS_MEMBER_REF"             , (void*)0 },
	{ ET_BINARYOPE, "GCC_OFS_ARRAY_REF"              , (void*)0 },
	{ ET_LIST     , "GCC_ATTRS"                      , (void*)0 },
	{ ET_BINARYOPE, "GCC_ATTR_ARG"                   , (void*)0 },
	{ ET_LIST     , "GCC_ATTR_ARGS"                  , (void*)0 },
	{ ET_BINARYOPE, "GCC_ASM_STMT"                   , (void*)0 },
	{ ET_UNARYOPE , "GCC_ASM_EXPR"                   , (void*)0 },
	{ ET_LIST     , "GCC_ASM_ARG"                    , (void*)0 },
	{ ET_LIST     , "GCC_ASM_OPE"                    , (void*)0 },
	{ ET_LIST     , "GCC_ASM_OPES"                   , (void*)0 },
	{ ET_LIST     , "GCC_ASM_CLOBS"                  , (void*)0 },
	{ ET_TERMINAL , "DIRECTIVE"                      , (void*)0 },
	{ ET_LIST     , "STRINGS"                        , (void*)0 },
	{ ET_LIST     , "DECL_SPECS"                     , (void*)0 },
	{ ET_LIST     , "LDECLARATOR"                    , (void*)0 },
	{ ET_BINARYOPE, "DATA_DECL"                      , (void*)0 },
	{ ET_LIST     , "DATA_DECLS"                     , (void*)0 },
	{ ET_BINARYOPE, "ARRAY_DECL"                     , (void*)0 },
	{ ET_BINARYOPE, "COARRAY_DECL"                   , (void*)0 },
	{ ET_TERMINAL , "POINTER_DECL"                   , (void*)0 },
	{ ET_BINARYOPE, "PARAM"                          , (void*)0 },
	{ ET_BINARYOPE, "TYPENAME"                       , (void*)0 },
	{ ET_TERMINAL , "SCSPEC"                         , (void*)0 },
	{ ET_TERMINAL , "TYPESPEC"                       , (void*)0 },
	{ ET_UNARYOPE , "ERROR_NODE"                     , (void*)0 },
	{ ET_TERMINAL , "TYPEQUAL"                       , (void*)0 },
	{ ET_UNARYOPE , "PRAGMA_PACK"                    , (void*)0 },
	{ ET_UNARYOPE , "XMP_DESC_OF"                    , (void*)0 }
};
