#define IDENTIFIER 257
#define TYPENAME 258
#define SCSPEC 259
#define STATIC 260
#define TYPESPEC 261
#define TYPEQUAL 262
#define CONSTANT 263
#define STRING 264
#define ELLIPSIS 265
#define COLON_SQBRACKET 266
#define ENUM 267
#define STRUCT 268
#define UNION 269
#define IF 270
#define ELSE 271
#define WHILE 272
#define DO 273
#define FOR 274
#define SWITCH 275
#define CASE 276
#define DEFAULT 277
#define BREAK 278
#define CONTINUE 279
#define RETURN 280
#define GOTO 281
#define SIZEOF 282
#define ARITH_LE 283
#define ARITH_GE 284
#define ARITH_EQ 285
#define ARITH_NE 286
#define PRAGMA 287
#define PRAGMA_ARG 288
#define DIRECTIVE 289
#define PRAGMA_PACK 290
#define PRAGMA_EXEC 291
#define PRAGMA_PREFIX 292
#define XMP_COARRAY_DECLARATION 293
#define XMP_CRITICAL 294
#define XMP_FUNC_CALL 295
#define XMP_DESC_OF 296
#define ASSEMBLER 297
#define LABEL 298
#define REALPART 299
#define IMAGPART 300
#define ATTRIBUTE 301
#define EXTENSION 302
#define TYPEOF 303
#define ALIGNOF 304
#define BLTIN_OFFSETOF 305
#define BLTIN_VA_ARG 306
#define BLTIN_TYPES_COMPATIBLE_P 307
#define OROR 308
#define ANDAND 309
#define LSHIFT 310
#define RSHIFT 311
#define HYPERUNARY 312
#define POINTSAT 313
#define ASSIGN 314
#define UNARY 315
#define PLUSPLUS 316
#define MINUSMINUS 317
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
    CExpr               *expr;
    CTypeSpecEnum       typespec;
    CAssignEnum         assigntype;
    CUnaryOpeEnum       unop;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
