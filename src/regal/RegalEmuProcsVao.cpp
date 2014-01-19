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
#include "RegalVao.h"
#include "RegalEmuProcsVao.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

static void REGAL_CALL emuProcInterceptVao_glBindBuffer(RegalContext *_context, GLenum target, GLuint buffer)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  _context->vao->ShadowBufferBinding( target, buffer );

  orig.glBindBuffer( _context, target, buffer );

}

static void REGAL_CALL emuProcInterceptVao_glBindBufferARB(RegalContext *_context, GLenum target, GLuint buffer)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  _context->vao->ShadowBufferBinding( target, buffer );

  orig.glBindBufferARB( _context, target, buffer );

}

static void REGAL_CALL emuProcInterceptVao_glBindVertexArray(RegalContext *_context, GLuint array)
{
  RegalAssert(_context);

  // impl
  _context->vao->BindVertexArray(*_context, array );

}

static void REGAL_CALL emuProcInterceptVao_glClientActiveTexture(RegalContext *_context, GLenum texture)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  _context->vao->ClientActiveTexture(*_context, texture );

  orig.glClientActiveTexture( _context, texture );

}

static void REGAL_CALL emuProcInterceptVao_glClientActiveTextureARB(RegalContext *_context, GLenum texture)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  _context->vao->ClientActiveTexture(*_context, texture );

  orig.glClientActiveTextureARB( _context, texture );

}

static void REGAL_CALL emuProcInterceptVao_glColorPointer(RegalContext *_context, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->ColorPointer(*_context, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glColorPointerEXT(RegalContext *_context, GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->ColorPointer(*_context, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glDeleteVertexArrays(RegalContext *_context, GLsizei n, const GLuint *arrays)
{
  RegalAssert(_context);

  // impl
  _context->vao->DeleteVertexArrays( n, arrays );

}

static void REGAL_CALL emuProcInterceptVao_glDisableClientState(RegalContext *_context, GLenum cap)
{
  RegalAssert(_context);

  // impl
  _context->vao->DisableClientState(*_context, cap );

}

static void REGAL_CALL emuProcInterceptVao_glDisableVertexAttribArray(RegalContext *_context, GLuint index)
{
  RegalAssert(_context);

  // impl
  return _context->vao->DisableVertexAttribArray(*_context, index );

}

static void REGAL_CALL emuProcInterceptVao_glDisableVertexAttribArrayARB(RegalContext *_context, GLuint index)
{
  RegalAssert(_context);

  // impl
  return _context->vao->DisableVertexAttribArray(*_context, index );

}

static void REGAL_CALL emuProcInterceptVao_glDrawArrays(RegalContext *_context, GLenum mode, GLint first, GLsizei count)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawArrays( _context, mode, first, count );

}

static void REGAL_CALL emuProcInterceptVao_glDrawArraysEXT(RegalContext *_context, GLenum mode, GLint first, GLsizei count)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawArraysEXT( _context, mode, first, count );

}

static void REGAL_CALL emuProcInterceptVao_glDrawArraysIndirect(RegalContext *_context, GLenum mode, const GLvoid *indirect)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawArraysIndirect( _context, mode, indirect );

}

static void REGAL_CALL emuProcInterceptVao_glDrawArraysInstanced(RegalContext *_context, GLenum mode, GLint start, GLsizei count, GLsizei primcount)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawArraysInstanced( _context, mode, start, count, primcount );

}

static void REGAL_CALL emuProcInterceptVao_glDrawArraysInstancedARB(RegalContext *_context, GLenum mode, GLint start, GLsizei count, GLsizei primcount)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawArraysInstancedARB( _context, mode, start, count, primcount );

}

static void REGAL_CALL emuProcInterceptVao_glDrawArraysInstancedEXT(RegalContext *_context, GLenum mode, GLint start, GLsizei count, GLsizei primcount)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawArraysInstancedEXT( _context, mode, start, count, primcount );

}

static void REGAL_CALL emuProcInterceptVao_glDrawElementArrayAPPLE(RegalContext *_context, GLenum mode, GLint first, GLsizei count)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawElementArrayAPPLE( _context, mode, first, count );

}

static void REGAL_CALL emuProcInterceptVao_glDrawElementArrayATI(RegalContext *_context, GLenum mode, GLsizei count)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawElementArrayATI( _context, mode, count );

}

static void REGAL_CALL emuProcInterceptVao_glDrawElements(RegalContext *_context, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawElements( _context, mode, count, type, indices );

}

static void REGAL_CALL emuProcInterceptVao_glDrawElementsBaseVertex(RegalContext *_context, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawElementsBaseVertex( _context, mode, count, type, indices, basevertex );

}

static void REGAL_CALL emuProcInterceptVao_glDrawElementsIndirect(RegalContext *_context, GLenum mode, GLenum type, const GLvoid *indirect)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawElementsIndirect( _context, mode, type, indirect );

}

static void REGAL_CALL emuProcInterceptVao_glDrawElementsInstanced(RegalContext *_context, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawElementsInstanced( _context, mode, count, type, indices, primcount );

}

static void REGAL_CALL emuProcInterceptVao_glDrawElementsInstancedARB(RegalContext *_context, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawElementsInstancedARB( _context, mode, count, type, indices, primcount );

}

static void REGAL_CALL emuProcInterceptVao_glDrawElementsInstancedBaseVertex(RegalContext *_context, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount, GLint basevertex)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawElementsInstancedBaseVertex( _context, mode, count, type, indices, primcount, basevertex );

}

static void REGAL_CALL emuProcInterceptVao_glDrawElementsInstancedEXT(RegalContext *_context, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glDrawElementsInstancedEXT( _context, mode, count, type, indices, primcount );

}

static void REGAL_CALL emuProcInterceptVao_glEnableClientState(RegalContext *_context, GLenum cap)
{
  RegalAssert(_context);

  // impl
  _context->vao->EnableClientState(*_context, cap );

}

static void REGAL_CALL emuProcInterceptVao_glEnableVertexAttribArray(RegalContext *_context, GLuint index)
{
  RegalAssert(_context);

  // impl
  return _context->vao->EnableVertexAttribArray(*_context, index );

}

static void REGAL_CALL emuProcInterceptVao_glEnableVertexAttribArrayARB(RegalContext *_context, GLuint index)
{
  RegalAssert(_context);

  // impl
  return _context->vao->EnableVertexAttribArray(*_context, index );

}

static void REGAL_CALL emuProcInterceptVao_glFogCoordPointer(RegalContext *_context, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->FogCoordPointer(*_context, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glFogCoordPointerEXT(RegalContext *_context, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->FogCoordPointer(*_context, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glGenVertexArrays(RegalContext *_context, GLsizei n, GLuint *arrays)
{
  RegalAssert(_context);

  // impl
  _context->vao->GenVertexArrays( n, arrays );

}

static void REGAL_CALL emuProcInterceptVao_glGetBooleanv(RegalContext *_context, GLenum pname, GLboolean *params)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // impl
  if( !_context->vao->Get( pname, params ) ) {
     orig.glGetBooleanv( _context, pname, params );
  }

}

static void REGAL_CALL emuProcInterceptVao_glGetDoublev(RegalContext *_context, GLenum pname, GLdouble *params)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // impl
  if( !_context->vao->Get( pname, params ) ) {
     orig.glGetDoublev( _context, pname, params );
  }

}

static void REGAL_CALL emuProcInterceptVao_glGetFloatv(RegalContext *_context, GLenum pname, GLfloat *params)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // impl
  if( !_context->vao->Get( pname, params ) ) {
     orig.glGetFloatv( _context, pname, params );
  }

}

static void REGAL_CALL emuProcInterceptVao_glGetInteger64v(RegalContext *_context, GLenum pname, GLint64 *params)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // impl
  if( !_context->vao->Get( pname, params ) ) {
     orig.glGetInteger64v( _context, pname, params );
  }

}

static void REGAL_CALL emuProcInterceptVao_glGetIntegerv(RegalContext *_context, GLenum pname, GLint *params)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // impl
  if( !_context->vao->Get( pname, params ) ) {
     orig.glGetIntegerv( _context, pname, params );
  }

}

static void REGAL_CALL emuProcInterceptVao_glGetVertexAttribPointerv(RegalContext *_context, GLuint index, GLenum pname, GLvoid **pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->GetAttrib( index, pname, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glGetVertexAttribPointervARB(RegalContext *_context, GLuint index, GLenum pname, GLvoid **pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->GetAttrib( index, pname, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glGetVertexAttribdv(RegalContext *_context, GLuint index, GLenum pname, GLdouble *params)
{
  RegalAssert(_context);

  // impl
  _context->vao->GetAttrib( index, pname, params );

}

static void REGAL_CALL emuProcInterceptVao_glGetVertexAttribdvARB(RegalContext *_context, GLuint index, GLenum pname, GLdouble *params)
{
  RegalAssert(_context);

  // impl
  _context->vao->GetAttrib( index, pname, params );

}

static void REGAL_CALL emuProcInterceptVao_glGetVertexAttribfv(RegalContext *_context, GLuint index, GLenum pname, GLfloat *params)
{
  RegalAssert(_context);

  // impl
  _context->vao->GetAttrib( index, pname, params );

}

static void REGAL_CALL emuProcInterceptVao_glGetVertexAttribfvARB(RegalContext *_context, GLuint index, GLenum pname, GLfloat *params)
{
  RegalAssert(_context);

  // impl
  _context->vao->GetAttrib( index, pname, params );

}

static void REGAL_CALL emuProcInterceptVao_glGetVertexAttribiv(RegalContext *_context, GLuint index, GLenum pname, GLint *params)
{
  RegalAssert(_context);

  // impl
  _context->vao->GetAttrib( index, pname, params );

}

static void REGAL_CALL emuProcInterceptVao_glGetVertexAttribivARB(RegalContext *_context, GLuint index, GLenum pname, GLint *params)
{
  RegalAssert(_context);

  // impl
  _context->vao->GetAttrib( index, pname, params );

}

static void REGAL_CALL emuProcInterceptVao_glInterleavedArrays(RegalContext *_context, GLenum format, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->InterleavedArrays(*_context, format, stride, pointer );

}

static GLboolean REGAL_CALL emuProcInterceptVao_glIsVertexArray(RegalContext *_context, GLuint array)
{
  RegalAssert(_context);

  // impl
  return _context->vao->IsVertexArray( array );

}

static void REGAL_CALL emuProcInterceptVao_glMultiDrawArrays(RegalContext *_context, GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glMultiDrawArrays( _context, mode, first, count, primcount );

}

static void REGAL_CALL emuProcInterceptVao_glMultiDrawArraysEXT(RegalContext *_context, GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glMultiDrawArraysEXT( _context, mode, first, count, primcount );

}

static void REGAL_CALL emuProcInterceptVao_glMultiDrawArraysIndirect(RegalContext *_context, GLenum mode, const GLvoid *indirect, GLsizei primcount, GLsizei stride)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glMultiDrawArraysIndirect( _context, mode, indirect, primcount, stride );

}

static void REGAL_CALL emuProcInterceptVao_glMultiDrawArraysIndirectAMD(RegalContext *_context, GLenum mode, const GLvoid *indirect, GLsizei primcount, GLsizei stride)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glMultiDrawArraysIndirectAMD( _context, mode, indirect, primcount, stride );

}

static void REGAL_CALL emuProcInterceptVao_glMultiDrawElementArrayAPPLE(RegalContext *_context, GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glMultiDrawElementArrayAPPLE( _context, mode, first, count, primcount );

}

static void REGAL_CALL emuProcInterceptVao_glMultiDrawElements(RegalContext *_context, GLenum mode, const GLsizei *count, GLenum type, const GLvoid * const *indices, GLsizei primcount)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glMultiDrawElements( _context, mode, count, type, indices, primcount );

}

static void REGAL_CALL emuProcInterceptVao_glMultiDrawElementsBaseVertex(RegalContext *_context, GLenum mode, const GLsizei *count, GLenum type, const GLvoid * const *indices, GLsizei primcount, const GLint *basevertex)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glMultiDrawElementsBaseVertex( _context, mode, count, type, indices, primcount, basevertex );

}

static void REGAL_CALL emuProcInterceptVao_glMultiDrawElementsEXT(RegalContext *_context, GLenum mode, const GLsizei *count, GLenum type, const GLvoid **indices, GLsizei primcount)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glMultiDrawElementsEXT( _context, mode, count, type, indices, primcount );

}

static void REGAL_CALL emuProcInterceptVao_glMultiDrawElementsIndirect(RegalContext *_context, GLenum mode, GLenum type, const GLvoid *indirect, GLsizei primcount, GLsizei stride)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glMultiDrawElementsIndirect( _context, mode, type, indirect, primcount, stride );

}

static void REGAL_CALL emuProcInterceptVao_glMultiDrawElementsIndirectAMD(RegalContext *_context, GLenum mode, GLenum type, const GLvoid *indirect, GLsizei primcount, GLsizei stride)
{
  RegalAssert(_context);
  EmuProcsOriginateVao & orig = _context->vao->orig;

  // prefix
  // _context->vao->Validate(*_context );

  orig.glMultiDrawElementsIndirectAMD( _context, mode, type, indirect, primcount, stride );

}

static void REGAL_CALL emuProcInterceptVao_glNormalPointer(RegalContext *_context, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->NormalPointer(*_context, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glNormalPointerEXT(RegalContext *_context, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->NormalPointer(*_context, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glSecondaryColorPointer(RegalContext *_context, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->SecondaryColorPointer(*_context, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glSecondaryColorPointerEXT(RegalContext *_context, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->SecondaryColorPointer(*_context, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glTexCoordPointer(RegalContext *_context, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->TexCoordPointer(*_context, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glTexCoordPointerEXT(RegalContext *_context, GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->TexCoordPointer(*_context, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glVertexAttribPointer(RegalContext *_context, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  return _context->vao->AttribPointer(*_context, index, size, type, normalized, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glVertexAttribPointerARB(RegalContext *_context, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  return _context->vao->AttribPointer(*_context, index, size, type, normalized, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glVertexPointer(RegalContext *_context, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->VertexPointer(*_context, size, type, stride, pointer );

}

static void REGAL_CALL emuProcInterceptVao_glVertexPointerEXT(RegalContext *_context, GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer)
{
  RegalAssert(_context);

  // impl
  _context->vao->VertexPointer(*_context, size, type, stride, pointer );

}

void EmuProcsInterceptVao( Dispatch::GL & dt ) {
  dt.glBindBuffer                      = emuProcInterceptVao_glBindBuffer;
  dt.glBindBufferARB                   = emuProcInterceptVao_glBindBufferARB;
  dt.glBindVertexArray                 = emuProcInterceptVao_glBindVertexArray;
  dt.glClientActiveTexture             = emuProcInterceptVao_glClientActiveTexture;
  dt.glClientActiveTextureARB          = emuProcInterceptVao_glClientActiveTextureARB;
  dt.glColorPointer                    = emuProcInterceptVao_glColorPointer;
  dt.glColorPointerEXT                 = emuProcInterceptVao_glColorPointerEXT;
  dt.glDeleteVertexArrays              = emuProcInterceptVao_glDeleteVertexArrays;
  dt.glDisableClientState              = emuProcInterceptVao_glDisableClientState;
  dt.glDisableVertexAttribArray        = emuProcInterceptVao_glDisableVertexAttribArray;
  dt.glDisableVertexAttribArrayARB     = emuProcInterceptVao_glDisableVertexAttribArrayARB;
  dt.glDrawArrays                      = emuProcInterceptVao_glDrawArrays;
  dt.glDrawArraysEXT                   = emuProcInterceptVao_glDrawArraysEXT;
  dt.glDrawArraysIndirect              = emuProcInterceptVao_glDrawArraysIndirect;
  dt.glDrawArraysInstanced             = emuProcInterceptVao_glDrawArraysInstanced;
  dt.glDrawArraysInstancedARB          = emuProcInterceptVao_glDrawArraysInstancedARB;
  dt.glDrawArraysInstancedEXT          = emuProcInterceptVao_glDrawArraysInstancedEXT;
  dt.glDrawElementArrayAPPLE           = emuProcInterceptVao_glDrawElementArrayAPPLE;
  dt.glDrawElementArrayATI             = emuProcInterceptVao_glDrawElementArrayATI;
  dt.glDrawElements                    = emuProcInterceptVao_glDrawElements;
  dt.glDrawElementsBaseVertex          = emuProcInterceptVao_glDrawElementsBaseVertex;
  dt.glDrawElementsIndirect            = emuProcInterceptVao_glDrawElementsIndirect;
  dt.glDrawElementsInstanced           = emuProcInterceptVao_glDrawElementsInstanced;
  dt.glDrawElementsInstancedARB        = emuProcInterceptVao_glDrawElementsInstancedARB;
  dt.glDrawElementsInstancedBaseVertex = emuProcInterceptVao_glDrawElementsInstancedBaseVertex;
  dt.glDrawElementsInstancedEXT        = emuProcInterceptVao_glDrawElementsInstancedEXT;
  dt.glEnableClientState               = emuProcInterceptVao_glEnableClientState;
  dt.glEnableVertexAttribArray         = emuProcInterceptVao_glEnableVertexAttribArray;
  dt.glEnableVertexAttribArrayARB      = emuProcInterceptVao_glEnableVertexAttribArrayARB;
  dt.glFogCoordPointer                 = emuProcInterceptVao_glFogCoordPointer;
  dt.glFogCoordPointerEXT              = emuProcInterceptVao_glFogCoordPointerEXT;
  dt.glGenVertexArrays                 = emuProcInterceptVao_glGenVertexArrays;
  dt.glGetBooleanv                     = emuProcInterceptVao_glGetBooleanv;
  dt.glGetDoublev                      = emuProcInterceptVao_glGetDoublev;
  dt.glGetFloatv                       = emuProcInterceptVao_glGetFloatv;
  dt.glGetInteger64v                   = emuProcInterceptVao_glGetInteger64v;
  dt.glGetIntegerv                     = emuProcInterceptVao_glGetIntegerv;
  dt.glGetVertexAttribPointerv         = emuProcInterceptVao_glGetVertexAttribPointerv;
  dt.glGetVertexAttribPointervARB      = emuProcInterceptVao_glGetVertexAttribPointervARB;
  dt.glGetVertexAttribdv               = emuProcInterceptVao_glGetVertexAttribdv;
  dt.glGetVertexAttribdvARB            = emuProcInterceptVao_glGetVertexAttribdvARB;
  dt.glGetVertexAttribfv               = emuProcInterceptVao_glGetVertexAttribfv;
  dt.glGetVertexAttribfvARB            = emuProcInterceptVao_glGetVertexAttribfvARB;
  dt.glGetVertexAttribiv               = emuProcInterceptVao_glGetVertexAttribiv;
  dt.glGetVertexAttribivARB            = emuProcInterceptVao_glGetVertexAttribivARB;
  dt.glInterleavedArrays               = emuProcInterceptVao_glInterleavedArrays;
  dt.glIsVertexArray                   = emuProcInterceptVao_glIsVertexArray;
  dt.glMultiDrawArrays                 = emuProcInterceptVao_glMultiDrawArrays;
  dt.glMultiDrawArraysEXT              = emuProcInterceptVao_glMultiDrawArraysEXT;
  dt.glMultiDrawArraysIndirect         = emuProcInterceptVao_glMultiDrawArraysIndirect;
  dt.glMultiDrawArraysIndirectAMD      = emuProcInterceptVao_glMultiDrawArraysIndirectAMD;
  dt.glMultiDrawElementArrayAPPLE      = emuProcInterceptVao_glMultiDrawElementArrayAPPLE;
  dt.glMultiDrawElements               = emuProcInterceptVao_glMultiDrawElements;
  dt.glMultiDrawElementsBaseVertex     = emuProcInterceptVao_glMultiDrawElementsBaseVertex;
  dt.glMultiDrawElementsEXT            = emuProcInterceptVao_glMultiDrawElementsEXT;
  dt.glMultiDrawElementsIndirect       = emuProcInterceptVao_glMultiDrawElementsIndirect;
  dt.glMultiDrawElementsIndirectAMD    = emuProcInterceptVao_glMultiDrawElementsIndirectAMD;
  dt.glNormalPointer                   = emuProcInterceptVao_glNormalPointer;
  dt.glNormalPointerEXT                = emuProcInterceptVao_glNormalPointerEXT;
  dt.glSecondaryColorPointer           = emuProcInterceptVao_glSecondaryColorPointer;
  dt.glSecondaryColorPointerEXT        = emuProcInterceptVao_glSecondaryColorPointerEXT;
  dt.glTexCoordPointer                 = emuProcInterceptVao_glTexCoordPointer;
  dt.glTexCoordPointerEXT              = emuProcInterceptVao_glTexCoordPointerEXT;
  dt.glVertexAttribPointer             = emuProcInterceptVao_glVertexAttribPointer;
  dt.glVertexAttribPointerARB          = emuProcInterceptVao_glVertexAttribPointerARB;
  dt.glVertexPointer                   = emuProcInterceptVao_glVertexPointer;
  dt.glVertexPointerEXT                = emuProcInterceptVao_glVertexPointerEXT;
}

REGAL_NAMESPACE_END

#endif // REGAL_EMULATION