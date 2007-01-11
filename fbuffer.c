/*
 * CG Madness - a Marble Madness clone
 * Copyright (C) 2007  Sven Reinck
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * $Id$
 *
 */

#include "fbuffer.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include <stdio.h>

/*
 * Erzeugt einen Framebuffer und wei�t ihn einer bestimmten Texture zu
 */
int createFBuffer(int width, int height, unsigned int target, unsigned int color_tex, RenderTarget* context) {
	unsigned int fb;
	unsigned int depth_stencil_rb;

  glGenFramebuffersEXT(1, &fb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, target, color_tex, 0);

	/* initialize depth renderbuffer */
	glGenRenderbuffersEXT(1, &depth_stencil_rb);

	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_stencil_rb);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH24_STENCIL8_EXT, width, height);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_stencil_rb);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_stencil_rb);

	{
		GLenum status;
		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		switch (status) {
			case GL_FRAMEBUFFER_COMPLETE_EXT:
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
				printf("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT\n");
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
				printf("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT\n");
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
				printf("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT\n");
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
				printf("GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT\n");
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
				printf("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT\n");
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
				printf("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT\n");
				break;
			case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
				printf("GL_FRAMEBUFFER_UNSUPPORTED_EXT\n");
				break;
			default:
				printf("unkown staus!\n");
				break;
		}

		if (status != GL_FRAMEBUFFER_COMPLETE_EXT) {
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
			return 0;
		}
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	context->width = width;
	context->height = height;
	context->framebuffer = fb;
	context->texTarget = target;
	context->texID = color_tex;
	context->viewport = NULL;

	return 1;
}

/*
 * Erzeugt einen RenderToTexture-Framebuffer
 */
int initFBuffer(int width, int height, RenderTarget* context) {
	unsigned int color_tex;

	/* initialize color texture */
  glGenTextures(1, &color_tex);
	glBindTexture(GL_TEXTURE_2D, color_tex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	/* Randbehandlung: Wiederholung */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/* Linerare Interpolation bei Skalierung der Textur */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (createFBuffer(width, height, GL_TEXTURE_2D, color_tex, context)) {
		return color_tex;
	}	else {
		return 0;
	}
}

/*
 * Erzeugt einen RenderToCubeMap-Framebuffer
 */
int initFBufferCube(int width, int height, RenderTarget context[6]) {
	unsigned int color_tex;
	int i;

	/* initialize color texture */
  glGenTextures(1, &color_tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, color_tex);

	for (i = 0; i < 6; i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	}

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (!createFBuffer(width, height, GL_TEXTURE_CUBE_MAP_POSITIVE_X, color_tex, &context[0])) {
		return 0;
	}

	for (i = 1; i < 6; i++) {
		context[i].width = width;
		context[i].height = height;
		context[i].framebuffer = context[0].framebuffer;
		context[i].texTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		context[i].texID = color_tex;
		context[i].viewport = NULL;
	}

	return color_tex;
}
