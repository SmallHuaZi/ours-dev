/* Copyright 2017 - 2024 R. Thomas
 * Copyright 2017 - 2024 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef LIEF_VERSION_H
#define LIEF_VERSION_H

#if defined(NDEBUG)
  #define LIEF_NAME "LIEF"
#else
  #define LIEF_NAME "LIEF (Debug)"
#endif

#define LIEF_VERSION "0.16.4-10f74acf"
#define LIEF_TAGGED 
#define LIEF_TAG    ""
#define LIEF_COMMIT "10f74acf"

#define HUMAN_VERSION " v" LIEF_VERSION
#define HUMAN_NAME NAME HUMAN_VERSION

#endif
