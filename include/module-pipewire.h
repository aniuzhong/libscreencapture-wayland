/*******************************************************************************
   Copyright © 2022-2023 by DafabHoid <github@dafaboid.de>

   SPDX-License-Identifier: GPL-3.0-or-later
*******************************************************************************/
#ifndef SCREENCAPTURE_MODULE_PIPEWIRE_H
#define SCREENCAPTURE_MODULE_PIPEWIRE_H

#include "c_common.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif
enum PipeWireStream_EventType
{
	PWSTREAM_EVENT_TYPE_CONNECTED,
	PWSTREAM_EVENT_TYPE_DISCONNECTED,
	PWSTREAM_EVENT_TYPE_MEMORY_FRAME_RECEIVED,
	PWSTREAM_EVENT_TYPE_DMA_BUF_RECEIVED,
};

struct PipeWireStream_Event_Connect
{
	struct Rect dimensions;
	enum PixelFormat format;
	bool isDmaBuf;
};
struct PipeWireStream_Event_Disconnect
{
	char dummy;
};
struct PipeWireStream_Event_MemoryFrameReceived
{
	const struct MemoryFrame* frame;
};
struct PipeWireStream_Event_DmaBufFrameReceived
{
	const struct DmaBufFrame* frame;
};

struct PipeWireStream_Event
{
	enum PipeWireStream_EventType type;
	union
	{
		struct PipeWireStream_Event_Connect connect;
		struct PipeWireStream_Event_Disconnect disconnect;
		struct PipeWireStream_Event_MemoryFrameReceived memoryFrameReceived;
		struct PipeWireStream_Event_DmaBufFrameReceived dmaBufFrameReceived;
	};
};

struct PipeWireStream;

SCW_EXPORT struct PipeWireStream* PipeWireStream_connect(const SharedScreen_t* shareInfo);

SCW_EXPORT void PipeWireStream_free(struct PipeWireStream* stream);

SCW_EXPORT int PipeWireStream_getEventPollFd(struct PipeWireStream* stream);

SCW_EXPORT int PipeWireStream_nextEvent(struct PipeWireStream* stream, struct PipeWireStream_Event* e);

#ifdef __cplusplus
} // extern "C"
#endif


#endif //SCREENCAPTURE_MODULE_PIPEWIRE_H