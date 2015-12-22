/*
 * Copyright (C) 2015  Mozilla Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <assert.h>
#include <fdio/task.h>
#include <hardware/tv_input.h>
#include <hardware_legacy/power.h>
#include "log.h"
#include "pdubuf.h"
#include "thread.h"
#include "wakelock.h"
#include "dvb_t.h"

enum {
  /* commands/responses */
  OPCODE_GET_TUNERS = 0x01,
  OPCODE_SET_SOURCE = 0x02,
  OPCODE_START_SCAN = 0x03,
  OPCODE_STOP_SCAN = 0x04,
  OPCODE_CLEAR_CACHE = 0x05,
  OPCODE_SET_CHANNEL = 0x06,
  OPCODE_GET_CHANNEL = 0x07,
  OPCODE_GET_PROGRAM = 0x08,
  OPCODE_GET_STREAM = 0x09,
  OPCODE_ACK = 0x10,
  /* notifications */
  OPCODE_CHANNEL_SCANNED = 0x81,
  OPCODE_SCANNED_COMPLETE = 0x82,
  OPCODE_SCAN_STOPPED = 0x83,
  OPCODE_EIT_BROADCASTED = 0x84
};

static void (*send_pdu)(struct pdu_wbuf* wbuf);

/*
 * Protocol helpers
 */

/*
 * Notifications
 */

/*
 * Commands/Responses
 */
static int
ack(const struct pdu* cmd)
{
  struct pdu_wbuf* wbuf;
  int err;
  wbuf = create_pdu_wbuf(0, 0, NULL);
  if (!wbuf)
    return ERROR_NOMEM;

  init_pdu(&wbuf->buf.pdu, cmd->service, cmd->opcode);
  send_pdu(wbuf);

  return ERROR_NONE;
}


static int
tv_handler(const struct pdu* cmd)
{
  static int (* const handler[256])(const struct pdu*) = {
/*    [OPCODE_GET_TUNERS] = get_tuners,
    [OPCODE_SET_SOURCE] = set_source,
    [OPCODE_START_SCAN] = start_scan,
    [OPCODE_STOP_SCAN] = stop_scan,
    [OPCODE_CLEAR_CACHE] = clear_cache,
    [OPCODE_SET_CHANNEL] = set_channel,
    [OPCODE_GET_CHANNEL] = get_channel,
    [OPCODE_GET_PROGRAM] = get_program,
    [OPCODE_GET_STREAM] = get_stream*/
    [OPCODE_ACK] = ack
  };

  return handle_pdu_by_opcode(cmd, handler);
}

int
(*register_tv(void (*send_pdu_cb)(struct pdu_wbuf*)))(const struct pdu*)
{
  send_pdu = send_pdu_cb;

  return tv_handler;
}

int
unregister_tv()
{
  return 0;
}

