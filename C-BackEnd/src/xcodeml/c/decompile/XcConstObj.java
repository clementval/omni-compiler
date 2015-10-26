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
package xcodeml.c.decompile;

import java.math.BigInteger;

import xcodeml.XmException;
import xcodeml.c.obj.XcNode;
import xcodeml.c.type.XcBaseType;
import xcodeml.c.type.XcBaseTypeEnum;
import xcodeml.c.type.XcPointerType;
import xcodeml.c.type.XcType;
import xcodeml.c.util.XmcTypeUtil;
import xcodeml.c.util.XmcWriter;
import xcodeml.util.XmBindingException;
import xcodeml.util.XmStringUtil;

/**
 * Internal object represents following elements:
 *   intConst, longLongConst, floatConst, stringConst
 */
public abstract class XcConstObj extends XcObj implements XcExprObj
{
    private XcType _type;

    private XcConstObj(XcType type)
    {
        _type = type;
    }

    /**
     * Gets a type of constant value.
     * 
     * @return a type of constant value.
     */
    public final XcType getType()
    {
        return _type;
    }

    @Override
    public void addChild(XcNode child)
    {
        throw new IllegalArgumentException(child.getClass().getName());
    }

    @Override
    public void checkChild()
    {
    }

    @Override
    public XcNode[] getChild()
    {
        return null;
    }

    private static void _appendNumberLiteral(XmcWriter w, XcType type, String n)
    {
        XcBaseTypeEnum btEnum = ((XcBaseType)type).getBaseTypeEnum();
        String suffix = btEnum.getLiteralSuffix();
        String cast = null;

        if(suffix == null) {
            switch(btEnum)
            {
            case INT:
            case DOUBLE:
                break;
            default:
                cast = "(" + btEnum.getCCode() + ")";
                break;
            }
        }
        w.spc().add(cast).add(n).add(suffix);
    }

    @Override
    public final void setChild(int index, XcNode child)
    {
        throw new IllegalArgumentException(index + ":" + child.getClass().getName());
    }

    /**
     * Internal object represents intConst.
     */
    public static final class IntConst extends XcConstObj
    {
        private long _value;

        private String _valueStr;

        /**
         * Creates IntConst.
         * 
         * @param value a value of the object.
         * @param typeEnum indicates the type of a value.
         */
        public IntConst(long value, XcBaseTypeEnum typeEnum)
        {
            super(typeEnum.getSingletonConstType());
            _value = value;
        }

        /**
         * Creates IntConst.
         * 
         * @param value a value of the object.
         * @param typeEnum indicates the type of a value.
         * @throws XmException thrown if a value does not represent integer.
         */
        public IntConst(String value, XcBaseTypeEnum typeEnum) throws XmException
        {
            this(XmStringUtil.getAsCLong(value, XmStringUtil.Radix.ALL), typeEnum);

            _valueStr = value;
        }

        @Override
        public final void appendCode(XmcWriter w) throws XmException
        {
            if(_valueStr != null) {
                _appendNumberLiteral(w, getType(), "" + _valueStr);
            } else {
                _appendNumberLiteral(w, getType(), "" + _value);
            }
        }
    }

    /**
     * Internal object represents longLongConst.
     */
    public static final class LongLongConst extends XcConstObj
    {
        private long _high, _low;

        private String _highStr, _lowStr;

        /**
         * Creates LongLongConst
         * 
         * @param high a forward 32 bit value of long long constant.
         * @param low a backward 32 bit value of long long constant.
         * @param typeEnum indicates type of value.
         */
        public LongLongConst(long high, long low, XcBaseTypeEnum typeEnum)
        {
            super(typeEnum.getSingletonConstType());
            _high = high;
            _low = low;
        }

        /**
         * Creates LongLongConst
         * 
         * @param high a forward 32 bit value of long long constant.
         * @param low a backward 32 bit value of long long constant.
         * @param typeEnum indicates type of value.
         * @throws XmException thrown if a value does not represent integer.
         */
        public LongLongConst(String hvalue, String lvalue, XcBaseTypeEnum typeEnum) throws XmException
        {
            this(
                XmStringUtil.getAsCLong(hvalue, XmStringUtil.Radix.HEX),
                XmStringUtil.getAsCLong(lvalue, XmStringUtil.Radix.HEX),
                typeEnum);

            if(hvalue.startsWith("0x")) {
                _highStr = hvalue.substring(2, hvalue.length());
            } else {
                throw new XmBindingException(null, "invalid hex integer value '" + hvalue + "'");
            }

            if(lvalue.startsWith("0x")) {
                _lowStr = "00000000" + lvalue.substring(2, lvalue.length());
                _lowStr = _lowStr.substring(_lowStr.length() - 8, _lowStr.length());
            } else {
                throw new XmBindingException(null, "invalid hex integer value '" + hvalue + "'");
            }
        }

        /**
         * get high bits value
         */
        public long getHigh()
        {
            return _high;
        }
        
        /**
         * get low bits value
         */
        public long getLow()
        {
            return _low;
        }

        @Override
        public final void appendCode(XmcWriter w) throws XmException
        {
            if(_highStr == null || _lowStr == null) {
                BigInteger n = new BigInteger("" + _high).shiftLeft(32).or(new BigInteger("" + _low));
                _appendNumberLiteral(w, getType(), n.toString());
            } else {
                _appendNumberLiteral(w, getType(), "0x" + _highStr + _lowStr);
            }
        }
    }

    /**
     * Internal object represets floatConst.
     */
    public static final class FloatConst extends XcConstObj
    {
        /* float constant literal */
        private String _floatLiteral;

        /**
         * Creates FloatConst.
         * 
         * @param floatLiteral represents a value of the object.
         * @param typeEnum indicates a type of a value.
         */
        public FloatConst(String floatLiteral, XcBaseTypeEnum typeEnum)
        {
            super(typeEnum.getSingletonConstType());
            _floatLiteral = floatLiteral;
        }

        @Override
        public final void appendCode(XmcWriter w) throws XmException
        {
            _appendNumberLiteral(w, getType(), "" + _floatLiteral);
        }
    }

    /**
     * Internal object represents stringConst.
     */
    public static final class StringConst extends XcConstObj
    {
        private String _value;

        private boolean _isWide;

        private static XcPointerType s_chrPtrType = XmcTypeUtil.createConstCharConstPointer();

        /**
         *  Creates StringConst.
         *  
         * @param value a value of the object.
         */
        public StringConst(String value)
        {
            super(s_chrPtrType);
            _value = value;
        }

        /**
         * Sets is a string value is a wide character string.
         * 
         * @param enable true if is a wide character string.
         */
        public void setIsWide(boolean enable)
        {
            _isWide = enable;
        }

        /**
         * Tests is a string value is a wide character string.
         * 
         * @return true if is a wide character string.
         */
        public boolean isWide()
        {
            return _isWide;
        }

        /**
         * Gets a value of the object.
         * 
         * @return a value of the object.
         */
        public final String getValue()
        {
            return _value;
        }

        @Override
        public final void appendCode(XmcWriter w) throws XmException
        {
            if(_isWide)
                w.add("L");

            w.add('"').add(_value == null ? "" : _value).add('"');
        }
    }
}
