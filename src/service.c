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

#include "dvb_t.h"
#include "pdu.h"
#include "service.h"

int (*service_handler[256])(const struct pdu*);

register_func
  (* const register_service[256])(void (*)(struct pdu_wbuf*)) = {
  /* SERVICE_REGISTRY is special and not handled here */
  [SERVICE_DVB_T] = register_tv,
};

int (*unregister_service[256])() = {
  [SERVICE_DVB_T] = unregister_tv,
};
