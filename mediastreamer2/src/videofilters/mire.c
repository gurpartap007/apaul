/*
mediastreamer2 library - modular sound and video processing and streaming
Copyright (C) 2006  Simon MORLAT (simon.morlat@linphone.org)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifdef HAVE_CONFIG_H
#include "mediastreamer-config.h"
#endif

#include "mediastreamer2/mscommon.h"
#include "mediastreamer2/msvideo.h"
#include "mediastreamer2/msfilter.h"
#include "mediastreamer2/msticker.h"
#include "mediastreamer2/mswebcam.h"
#include "mediastreamer2/mediastream.h"

#include <math.h>


typedef struct _MireData{
	MSVideoSize vsize;
	MSPicture pict;
	int index;
	uint64_t starttime;
	float fps;
	mblk_t *pic;
}MireData;

void mire_init(MSFilter *f){
	MireData *d=ms_new0(MireData,1);
	d->vsize.width=MS_VIDEO_SIZE_CIF_W;
	d->vsize.height=MS_VIDEO_SIZE_CIF_H;
	d->fps=15;
	d->index=0;
	d->starttime=0;
	d->pic=NULL;
	f->data=d;
}

void mire_uninit(MSFilter *f){
	ms_free(f->data);
}

static void mire_preprocess(MSFilter *f){
	MireData *d=(MireData*)f->data;
	d->pic=ms_yuv_buf_alloc(&d->pict,d->vsize.width,d->vsize.height);
	memset(d->pic->b_rptr,0,d->pic->b_wptr-d->pic->b_rptr);
	d->starttime=f->ticker->time;
}

static void plane_draw(uint8_t *p, int w, int h, int lsz, int index, int color1, int color2){
	int i,j;
	
	for(i=0;i<h;++i){
		int tmp = index + (cos(4*(double)(i)/(double)h) * (w/8));
		for(j=0;j<w;++j){
			p[j]= (( ((i+tmp)/85) + ((j+tmp)/85)  ) & 0x1) ? color1 : color2;
		}
		p+=lsz;
	}
}

static void mire_draw(MireData *d){
	plane_draw(d->pict.planes[0],d->pict.w,d->pict.h,d->pict.strides[0],d->index*2,150,12);
	plane_draw(d->pict.planes[1],d->pict.w/2,d->pict.h/2,d->pict.strides[1],d->index,100,60);
	plane_draw(d->pict.planes[2],d->pict.w/2,d->pict.h/2,d->pict.strides[2],d->index,200,100);
}

static void mire_process(MSFilter *f){
	MireData *d=(MireData*)f->data;
	float elapsed=(float)(f->ticker->time-d->starttime);
	if ((elapsed*d->fps/1000.0)>d->index){
		mire_draw(d);
		ms_queue_put(f->outputs[0],dupb(d->pic));
		d->index++;
	}
}

void mire_postprocess(MSFilter *f){
	MireData *d=(MireData*)f->data;
	if (d->pic) {
		freemsg(d->pic);
		d->pic=NULL;
	}
}

static int mire_set_vsize(MSFilter *f, void* data){
	MireData *d=(MireData*)f->data;
	d->vsize=*(MSVideoSize*)data;
	return 0;
}

static int mire_set_fps(MSFilter *f, void* data){
	MireData *d=(MireData*)f->data;
	d->fps=*(float*)data;
	return 0;
}

static int mire_get_fmt(MSFilter *f, void* data){
	*(MSPixFmt*)data=MS_YUV420P;
	return 0;
}

static int mire_get_vsize(MSFilter *f, void* data){
	MireData *d=(MireData*)f->data;
	*(MSVideoSize*)data=d->vsize;
	return 0;
}

MSFilterMethod mire_methods[]={
	{	MS_FILTER_SET_VIDEO_SIZE, mire_set_vsize },
	{	MS_FILTER_SET_FPS		, mire_set_fps	},
	{	MS_FILTER_GET_PIX_FMT	, mire_get_fmt	},
	{	MS_FILTER_GET_VIDEO_SIZE, mire_get_vsize },
	{	0,0 }
};

MSFilterDesc ms_mire_desc={
	MS_MIRE_ID,
	"MSMire",
	"A filter that outputs synthetic moving picture",
	MS_FILTER_OTHER,
	NULL,
	0,
	1,
	mire_init,
	mire_preprocess,
	mire_process,
	mire_postprocess,
	mire_uninit,
	mire_methods
};

MS_FILTER_DESC_EXPORT(ms_mire_desc)

static void mire_detect(MSWebCamManager *obj);

static void mire_cam_init(MSWebCam *cam){
	cam->name=ms_strdup("Mire (synthetic moving picture)");
}

static MSFilter *mire_create_reader(MSWebCam *obj){
	return ms_filter_new_from_desc(&ms_mire_desc);
}

MSWebCamDesc ms_mire_webcam_desc={
	"Mire",
	&mire_detect,
	&mire_cam_init,
	&mire_create_reader,
	NULL
};

MSWebCamDesc *ms_mire_webcam_desc_get(void){
	return &ms_mire_webcam_desc;
}

static void mire_detect(MSWebCamManager *obj){
	char *debug = NULL;
#ifndef MS2_WINDOWS_UNIVERSAL
	debug = getenv("DEBUG");
#endif
	if (debug && atoi(debug)==1){
		MSWebCam *cam=ms_web_cam_new(&ms_mire_webcam_desc);
		ms_web_cam_manager_add_cam(obj,cam);
	}
}

