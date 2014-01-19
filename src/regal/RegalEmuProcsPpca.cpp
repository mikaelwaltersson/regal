/* NOTE: Do not edit this file, it is generated by a script:
   Export.py --api gl 4.4 --api wgl 4.4 --api glx 4.4 --api cgl 1.4 --api egl 1.0 --outdir .
*/

/*
  Copyright (c) 2011-2013 NVIDIA Corporation
  Copyright (c) 2011-2013 Cass Everitt
  Copyright (c) 2012-2013 Scott Nations
  Copyright (c) 2012 Mathias Schott
  Copyright (c) 2012-2013 Nigel Stewart
  Copyright (c) 2012-2013 Google Inc.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
  OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
  Intended formatting conventions:
  $ astyle --style=allman --indent=spaces=2 --indent-switches
*/

#include "RegalUtil.h"

#if REGAL_EMULATION

REGAL_GLOBAL_BEGIN

#include "RegalPrivate.h"
#include "RegalContext.h"
#include "RegalDispatch.h"
#include "RegalPpca.h"
#include "RegalEmuProcsPpca.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

static void REGAL_CALL emuProcInterceptPpca_glBindBuffer(RegalContext *_context, GLenum target, GLuint buffer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glBindBuffer( target, buffer );

  orig.glBindBuffer( _context, target, buffer );

}

static void REGAL_CALL emuProcInterceptPpca_glBindVertexArray(RegalContext *_context, GLuint array)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glBindVertexArray( array );

  orig.glBindVertexArray( _context, array );

}

static void REGAL_CALL emuProcInterceptPpca_glBindVertexBuffer(RegalContext *_context, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glBindVertexBuffer( bindingindex, buffer, offset, stride );

  orig.glBindVertexBuffer( _context, bindingindex, buffer, offset, stride );

}

static void REGAL_CALL emuProcInterceptPpca_glBindVertexBuffers(RegalContext *_context, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glBindVertexBuffers( first, count, buffers, offsets, strides );

  orig.glBindVertexBuffers( _context, first, count, buffers, offsets, strides );

}

static void REGAL_CALL emuProcInterceptPpca_glClientActiveTexture(RegalContext *_context, GLenum texture)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glClientActiveTexture( texture );

  orig.glClientActiveTexture( _context, texture );

}

static void REGAL_CALL emuProcInterceptPpca_glClientActiveTextureARB(RegalContext *_context, GLenum texture)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glClientActiveTexture( texture );

  orig.glClientActiveTextureARB( _context, texture );

}

static void REGAL_CALL emuProcInterceptPpca_glClientAttribDefaultEXT(RegalContext *_context, GLbitfield mask)
{
  RegalAssert(_context);

  // impl
  _context->ppca->glClientAttribDefaultEXT( *_context, mask );

}

static void REGAL_CALL emuProcInterceptPpca_glColorPointer(RegalContext *_context, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glColorPointer( size, type, stride, pointer );

  orig.glColorPointer( _context, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptPpca_glDeleteBuffers(RegalContext *_context, GLsizei n, const GLuint *buffers)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glDeleteBuffers( n, buffers );

  orig.glDeleteBuffers( _context, n, buffers );

}

static void REGAL_CALL emuProcInterceptPpca_glDeleteVertexArrays(RegalContext *_context, GLsizei n, const GLuint *arrays)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glDeleteVertexArrays( n, arrays );

  orig.glDeleteVertexArrays( _context, n, arrays );

}

static void REGAL_CALL emuProcInterceptPpca_glDisable(RegalContext *_context, GLenum cap)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glDisable( cap );

  orig.glDisable( _context, cap );

}

static void REGAL_CALL emuProcInterceptPpca_glDisableClientState(RegalContext *_context, GLenum cap)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glDisableClientState( cap );

  orig.glDisableClientState( _context, cap );

}

static void REGAL_CALL emuProcInterceptPpca_glDisableClientStateIndexedEXT(RegalContext *_context, GLenum array, GLuint index)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glDisableClientStateIndexedEXT( array, index );

  orig.glDisableClientStateIndexedEXT( _context, array, index );

}

static void REGAL_CALL emuProcInterceptPpca_glDisableClientStateiEXT(RegalContext *_context, GLenum array, GLuint index)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glDisableClientStateiEXT( array, index );

  orig.glDisableClientStateiEXT( _context, array, index );

}

static void REGAL_CALL emuProcInterceptPpca_glDisableIndexedEXT(RegalContext *_context, GLenum target, GLuint index)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glDisableIndexedEXT( target, index );

  orig.glDisableIndexedEXT( _context, target, index );

}

static void REGAL_CALL emuProcInterceptPpca_glDisableVertexArrayAttribEXT(RegalContext *_context, GLuint vaobj, GLenum array)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glDisableVertexArrayAttribEXT( vaobj, array );

  orig.glDisableVertexArrayAttribEXT( _context, vaobj, array );

}

static void REGAL_CALL emuProcInterceptPpca_glDisableVertexArrayEXT(RegalContext *_context, GLuint vaobj, GLenum array)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glDisableVertexArrayEXT( vaobj, array );

  orig.glDisableVertexArrayEXT( _context, vaobj, array );

}

static void REGAL_CALL emuProcInterceptPpca_glDisableVertexAttribArray(RegalContext *_context, GLuint index)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glDisableVertexAttribArray( index );

  orig.glDisableVertexAttribArray( _context, index );

}

static void REGAL_CALL emuProcInterceptPpca_glDisablei(RegalContext *_context, GLenum cap, GLuint index)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glDisablei( cap, index );

  orig.glDisablei( _context, cap, index );

}

static void REGAL_CALL emuProcInterceptPpca_glEdgeFlagPointer(RegalContext *_context, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glEdgeFlagPointer( stride, pointer );

  orig.glEdgeFlagPointer( _context, stride, pointer );

}

static void REGAL_CALL emuProcInterceptPpca_glEnable(RegalContext *_context, GLenum cap)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glEnable( cap );

  orig.glEnable( _context, cap );

}

static void REGAL_CALL emuProcInterceptPpca_glEnableClientState(RegalContext *_context, GLenum cap)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glEnableClientState( cap );

  orig.glEnableClientState( _context, cap );

}

static void REGAL_CALL emuProcInterceptPpca_glEnableClientStateIndexedEXT(RegalContext *_context, GLenum array, GLuint index)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glEnableClientStateIndexedEXT( array, index );

  orig.glEnableClientStateIndexedEXT( _context, array, index );

}

static void REGAL_CALL emuProcInterceptPpca_glEnableClientStateiEXT(RegalContext *_context, GLenum array, GLuint index)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glEnableClientStateiEXT( array, index );

  orig.glEnableClientStateiEXT( _context, array, index );

}

static void REGAL_CALL emuProcInterceptPpca_glEnableIndexedEXT(RegalContext *_context, GLenum target, GLuint index)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glEnableIndexedEXT( target, index );

  orig.glEnableIndexedEXT( _context, target, index );

}

static void REGAL_CALL emuProcInterceptPpca_glEnableVertexArrayAttribEXT(RegalContext *_context, GLuint vaobj, GLenum array)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glEnableVertexArrayAttribEXT( vaobj, array );

  orig.glEnableVertexArrayAttribEXT( _context, vaobj, array );

}

static void REGAL_CALL emuProcInterceptPpca_glEnableVertexArrayEXT(RegalContext *_context, GLuint vaobj, GLenum array)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glEnableVertexArrayEXT( vaobj, array );

  orig.glEnableVertexArrayEXT( _context, vaobj, array );

}

static void REGAL_CALL emuProcInterceptPpca_glEnableVertexAttribArray(RegalContext *_context, GLuint index)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glEnableVertexAttribArray( index );

  orig.glEnableVertexAttribArray( _context, index );

}

static void REGAL_CALL emuProcInterceptPpca_glEnablei(RegalContext *_context, GLenum cap, GLuint index)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glEnablei( cap, index );

  orig.glEnablei( _context, cap, index );

}

static void REGAL_CALL emuProcInterceptPpca_glFogCoordPointer(RegalContext *_context, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glFogCoordPointer( type, stride, pointer );

  orig.glFogCoordPointer( _context, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptPpca_glGetBooleanv(RegalContext *_context, GLenum pname, GLboolean *params)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // impl
  if ( ! _context->ppca->glGetv( *_context, pname, params ) ) {
    orig.glGetBooleanv( _context, pname, params );
  }

}

static void REGAL_CALL emuProcInterceptPpca_glGetDoublev(RegalContext *_context, GLenum pname, GLdouble *params)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // impl
  if ( ! _context->ppca->glGetv( *_context, pname, params ) ) {
    orig.glGetDoublev( _context, pname, params );
  }

}

static void REGAL_CALL emuProcInterceptPpca_glGetFloatv(RegalContext *_context, GLenum pname, GLfloat *params)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // impl
  if ( ! _context->ppca->glGetv( *_context, pname, params ) ) {
    orig.glGetFloatv( _context, pname, params );
  }

}

static void REGAL_CALL emuProcInterceptPpca_glGetIntegerv(RegalContext *_context, GLenum pname, GLint *params)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // impl
  if ( ! _context->ppca->glGetv( *_context, pname, params ) ) {
    orig.glGetIntegerv( _context, pname, params );
  }

}

static void REGAL_CALL emuProcInterceptPpca_glIndexPointer(RegalContext *_context, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glIndexPointer( type, stride, pointer );

  orig.glIndexPointer( _context, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptPpca_glInterleavedArrays(RegalContext *_context, GLenum format, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glInterleavedArrays( format, stride, pointer );

  orig.glInterleavedArrays( _context, format, stride, pointer );

}

static void REGAL_CALL emuProcInterceptPpca_glMultiTexCoordPointerEXT(RegalContext *_context, GLenum texunit, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glMultiTexCoordPointerEXT( texunit, size, type, stride, pointer );

  orig.glMultiTexCoordPointerEXT( _context, texunit, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptPpca_glNormalPointer(RegalContext *_context, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glNormalPointer( type, stride, pointer );

  orig.glNormalPointer( _context, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptPpca_glPixelStoref(RegalContext *_context, GLenum pname, GLfloat param)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glPixelStore( pname, param );

  orig.glPixelStoref( _context, pname, param );

}

static void REGAL_CALL emuProcInterceptPpca_glPixelStorei(RegalContext *_context, GLenum pname, GLint param)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glPixelStore( pname, param );

  orig.glPixelStorei( _context, pname, param );

}

static void REGAL_CALL emuProcInterceptPpca_glPopClientAttrib(RegalContext *_context)
{
  RegalAssert(_context);

  // impl
  _context->ppca->glPopClientAttrib( *_context );

}

static void REGAL_CALL emuProcInterceptPpca_glPrimitiveRestartIndex(RegalContext *_context, GLuint index)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glPrimitiveRestartIndex( index );

  orig.glPrimitiveRestartIndex( _context, index );

}

static void REGAL_CALL emuProcInterceptPpca_glPushClientAttrib(RegalContext *_context, GLbitfield mask)
{
  RegalAssert(_context);

  // impl
  _context->ppca->glPushClientAttrib( *_context, mask );

}

static void REGAL_CALL emuProcInterceptPpca_glPushClientAttribDefaultEXT(RegalContext *_context, GLbitfield mask)
{
  RegalAssert(_context);

  // impl
  _context->ppca->glPushClientAttribDefaultEXT( *_context, mask );

}

static void REGAL_CALL emuProcInterceptPpca_glSecondaryColorPointer(RegalContext *_context, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glSecondaryColorPointer( size, type, stride, pointer );

  orig.glSecondaryColorPointer( _context, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptPpca_glTexCoordPointer(RegalContext *_context, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glTexCoordPointer( size, type, stride, pointer );

  orig.glTexCoordPointer( _context, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexArrayColorOffsetEXT(RegalContext *_context, GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, const GLintptr offset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexArrayColorOffsetEXT( vaobj, buffer, size, type, stride, offset );

  orig.glVertexArrayColorOffsetEXT( _context, vaobj, buffer, size, type, stride, offset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexArrayEdgeFlagOffsetEXT(RegalContext *_context, GLuint vaobj, GLuint buffer, GLsizei stride, const GLintptr offset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexArrayEdgeFlagOffsetEXT( vaobj, buffer, stride, offset );

  orig.glVertexArrayEdgeFlagOffsetEXT( _context, vaobj, buffer, stride, offset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexArrayFogCoordOffsetEXT(RegalContext *_context, GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, const GLintptr offset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexArrayFogCoordOffsetEXT( vaobj, buffer, type, stride, offset );

  orig.glVertexArrayFogCoordOffsetEXT( _context, vaobj, buffer, type, stride, offset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexArrayIndexOffsetEXT(RegalContext *_context, GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, const GLintptr offset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexArrayIndexOffsetEXT( vaobj, buffer, type, stride, offset );

  orig.glVertexArrayIndexOffsetEXT( _context, vaobj, buffer, type, stride, offset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexArrayMultiTexCoordOffsetEXT(RegalContext *_context, GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, const GLintptr offset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexArrayMultiTexCoordOffsetEXT( vaobj, buffer, texunit, size, type, stride, offset );

  orig.glVertexArrayMultiTexCoordOffsetEXT( _context, vaobj, buffer, texunit, size, type, stride, offset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexArrayNormalOffsetEXT(RegalContext *_context, GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, const GLintptr offset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexArrayNormalOffsetEXT( vaobj, buffer, type, stride, offset );

  orig.glVertexArrayNormalOffsetEXT( _context, vaobj, buffer, type, stride, offset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexArraySecondaryColorOffsetEXT(RegalContext *_context, GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, const GLintptr offset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexArraySecondaryColorOffsetEXT( vaobj, buffer, size, type, stride, offset );

  orig.glVertexArraySecondaryColorOffsetEXT( _context, vaobj, buffer, size, type, stride, offset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexArrayTexCoordOffsetEXT(RegalContext *_context, GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, const GLintptr offset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexArrayTexCoordOffsetEXT( vaobj, buffer, size, type, stride, offset );

  orig.glVertexArrayTexCoordOffsetEXT( _context, vaobj, buffer, size, type, stride, offset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexArrayVertexAttribIOffsetEXT(RegalContext *_context, GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, const GLintptr offset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexArrayVertexAttribIOffsetEXT( vaobj, buffer, index, size, type, stride, offset );

  orig.glVertexArrayVertexAttribIOffsetEXT( _context, vaobj, buffer, index, size, type, stride, offset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexArrayVertexAttribOffsetEXT(RegalContext *_context, GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLintptr offset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexArrayVertexAttribOffsetEXT( vaobj, buffer, index, size, type, normalized, stride, offset );

  orig.glVertexArrayVertexAttribOffsetEXT( _context, vaobj, buffer, index, size, type, normalized, stride, offset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexArrayVertexOffsetEXT(RegalContext *_context, GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, const GLintptr offset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexArrayVertexOffsetEXT( vaobj, buffer, size, type, stride, offset );

  orig.glVertexArrayVertexOffsetEXT( _context, vaobj, buffer, size, type, stride, offset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexAttribBinding(RegalContext *_context, GLuint attribindex, GLuint bindingindex)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexAttribBinding( attribindex, bindingindex );

  orig.glVertexAttribBinding( _context, attribindex, bindingindex );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexAttribDivisor(RegalContext *_context, GLuint index, GLuint divisor)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexAttribDivisor( index, divisor );

  orig.glVertexAttribDivisor( _context, index, divisor );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexAttribFormat(RegalContext *_context, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexAttribFormat( attribindex, size, type, normalized, relativeoffset );

  orig.glVertexAttribFormat( _context, attribindex, size, type, normalized, relativeoffset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexAttribIFormat(RegalContext *_context, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexAttribIFormat( attribindex, size, type, relativeoffset );

  orig.glVertexAttribIFormat( _context, attribindex, size, type, relativeoffset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexAttribIPointer(RegalContext *_context, GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexAttribIPointer( index, size, type, stride, pointer );

  orig.glVertexAttribIPointer( _context, index, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexAttribLFormat(RegalContext *_context, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexAttribLFormat( attribindex, size, type, relativeoffset );

  orig.glVertexAttribLFormat( _context, attribindex, size, type, relativeoffset );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexAttribLPointer(RegalContext *_context, GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexAttribLPointer( index, size, type, stride, pointer );

  orig.glVertexAttribLPointer( _context, index, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexAttribPointer(RegalContext *_context, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexAttribPointer( index, size, type, normalized, stride, pointer );

  orig.glVertexAttribPointer( _context, index, size, type, normalized, stride, pointer );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexBindingDivisor(RegalContext *_context, GLuint bindingindex, GLuint divisor)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexBindingDivisor( bindingindex, divisor );

  orig.glVertexBindingDivisor( _context, bindingindex, divisor );

}

static void REGAL_CALL emuProcInterceptPpca_glVertexPointer(RegalContext *_context, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);
  EmuProcsOriginatePpca & orig = _context->ppca->orig;

  // prefix
  _context->ppca->glVertexPointer( size, type, stride, pointer );

  orig.glVertexPointer( _context, size, type, stride, pointer );

}

void EmuProcsInterceptPpca( Dispatch::GL & dt ) {
  dt.glBindBuffer                         = emuProcInterceptPpca_glBindBuffer;
  dt.glBindVertexArray                    = emuProcInterceptPpca_glBindVertexArray;
  dt.glBindVertexBuffer                   = emuProcInterceptPpca_glBindVertexBuffer;
  dt.glBindVertexBuffers                  = emuProcInterceptPpca_glBindVertexBuffers;
  dt.glClientActiveTexture                = emuProcInterceptPpca_glClientActiveTexture;
  dt.glClientActiveTextureARB             = emuProcInterceptPpca_glClientActiveTextureARB;
  dt.glClientAttribDefaultEXT             = emuProcInterceptPpca_glClientAttribDefaultEXT;
  dt.glColorPointer                       = emuProcInterceptPpca_glColorPointer;
  dt.glDeleteBuffers                      = emuProcInterceptPpca_glDeleteBuffers;
  dt.glDeleteVertexArrays                 = emuProcInterceptPpca_glDeleteVertexArrays;
  dt.glDisable                            = emuProcInterceptPpca_glDisable;
  dt.glDisableClientState                 = emuProcInterceptPpca_glDisableClientState;
  dt.glDisableClientStateIndexedEXT       = emuProcInterceptPpca_glDisableClientStateIndexedEXT;
  dt.glDisableClientStateiEXT             = emuProcInterceptPpca_glDisableClientStateiEXT;
  dt.glDisableIndexedEXT                  = emuProcInterceptPpca_glDisableIndexedEXT;
  dt.glDisableVertexArrayAttribEXT        = emuProcInterceptPpca_glDisableVertexArrayAttribEXT;
  dt.glDisableVertexArrayEXT              = emuProcInterceptPpca_glDisableVertexArrayEXT;
  dt.glDisableVertexAttribArray           = emuProcInterceptPpca_glDisableVertexAttribArray;
  dt.glDisablei                           = emuProcInterceptPpca_glDisablei;
  dt.glEdgeFlagPointer                    = emuProcInterceptPpca_glEdgeFlagPointer;
  dt.glEnable                             = emuProcInterceptPpca_glEnable;
  dt.glEnableClientState                  = emuProcInterceptPpca_glEnableClientState;
  dt.glEnableClientStateIndexedEXT        = emuProcInterceptPpca_glEnableClientStateIndexedEXT;
  dt.glEnableClientStateiEXT              = emuProcInterceptPpca_glEnableClientStateiEXT;
  dt.glEnableIndexedEXT                   = emuProcInterceptPpca_glEnableIndexedEXT;
  dt.glEnableVertexArrayAttribEXT         = emuProcInterceptPpca_glEnableVertexArrayAttribEXT;
  dt.glEnableVertexArrayEXT               = emuProcInterceptPpca_glEnableVertexArrayEXT;
  dt.glEnableVertexAttribArray            = emuProcInterceptPpca_glEnableVertexAttribArray;
  dt.glEnablei                            = emuProcInterceptPpca_glEnablei;
  dt.glFogCoordPointer                    = emuProcInterceptPpca_glFogCoordPointer;
  dt.glGetBooleanv                        = emuProcInterceptPpca_glGetBooleanv;
  dt.glGetDoublev                         = emuProcInterceptPpca_glGetDoublev;
  dt.glGetFloatv                          = emuProcInterceptPpca_glGetFloatv;
  dt.glGetIntegerv                        = emuProcInterceptPpca_glGetIntegerv;
  dt.glIndexPointer                       = emuProcInterceptPpca_glIndexPointer;
  dt.glInterleavedArrays                  = emuProcInterceptPpca_glInterleavedArrays;
  dt.glMultiTexCoordPointerEXT            = emuProcInterceptPpca_glMultiTexCoordPointerEXT;
  dt.glNormalPointer                      = emuProcInterceptPpca_glNormalPointer;
  dt.glPixelStoref                        = emuProcInterceptPpca_glPixelStoref;
  dt.glPixelStorei                        = emuProcInterceptPpca_glPixelStorei;
  dt.glPopClientAttrib                    = emuProcInterceptPpca_glPopClientAttrib;
  dt.glPrimitiveRestartIndex              = emuProcInterceptPpca_glPrimitiveRestartIndex;
  dt.glPushClientAttrib                   = emuProcInterceptPpca_glPushClientAttrib;
  dt.glPushClientAttribDefaultEXT         = emuProcInterceptPpca_glPushClientAttribDefaultEXT;
  dt.glSecondaryColorPointer              = emuProcInterceptPpca_glSecondaryColorPointer;
  dt.glTexCoordPointer                    = emuProcInterceptPpca_glTexCoordPointer;
  dt.glVertexArrayColorOffsetEXT          = emuProcInterceptPpca_glVertexArrayColorOffsetEXT;
  dt.glVertexArrayEdgeFlagOffsetEXT       = emuProcInterceptPpca_glVertexArrayEdgeFlagOffsetEXT;
  dt.glVertexArrayFogCoordOffsetEXT       = emuProcInterceptPpca_glVertexArrayFogCoordOffsetEXT;
  dt.glVertexArrayIndexOffsetEXT          = emuProcInterceptPpca_glVertexArrayIndexOffsetEXT;
  dt.glVertexArrayMultiTexCoordOffsetEXT  = emuProcInterceptPpca_glVertexArrayMultiTexCoordOffsetEXT;
  dt.glVertexArrayNormalOffsetEXT         = emuProcInterceptPpca_glVertexArrayNormalOffsetEXT;
  dt.glVertexArraySecondaryColorOffsetEXT = emuProcInterceptPpca_glVertexArraySecondaryColorOffsetEXT;
  dt.glVertexArrayTexCoordOffsetEXT       = emuProcInterceptPpca_glVertexArrayTexCoordOffsetEXT;
  dt.glVertexArrayVertexAttribIOffsetEXT  = emuProcInterceptPpca_glVertexArrayVertexAttribIOffsetEXT;
  dt.glVertexArrayVertexAttribOffsetEXT   = emuProcInterceptPpca_glVertexArrayVertexAttribOffsetEXT;
  dt.glVertexArrayVertexOffsetEXT         = emuProcInterceptPpca_glVertexArrayVertexOffsetEXT;
  dt.glVertexAttribBinding                = emuProcInterceptPpca_glVertexAttribBinding;
  dt.glVertexAttribDivisor                = emuProcInterceptPpca_glVertexAttribDivisor;
  dt.glVertexAttribFormat                 = emuProcInterceptPpca_glVertexAttribFormat;
  dt.glVertexAttribIFormat                = emuProcInterceptPpca_glVertexAttribIFormat;
  dt.glVertexAttribIPointer               = emuProcInterceptPpca_glVertexAttribIPointer;
  dt.glVertexAttribLFormat                = emuProcInterceptPpca_glVertexAttribLFormat;
  dt.glVertexAttribLPointer               = emuProcInterceptPpca_glVertexAttribLPointer;
  dt.glVertexAttribPointer                = emuProcInterceptPpca_glVertexAttribPointer;
  dt.glVertexBindingDivisor               = emuProcInterceptPpca_glVertexBindingDivisor;
  dt.glVertexPointer                      = emuProcInterceptPpca_glVertexPointer;
}

REGAL_NAMESPACE_END

#endif // REGAL_EMULATION