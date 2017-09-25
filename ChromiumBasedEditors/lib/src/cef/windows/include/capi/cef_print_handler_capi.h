// Copyright (c) 2017 Marshall A. Greenblatt. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the name Chromium Embedded
// Framework nor the names of its contributors may be used to endorse
// or promote products derived from this software without specific prior
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//
// $hash=897f5b1ec6ed7430fff156f47b4ce6371d5db6f2$
//

#ifndef CEF_INCLUDE_CAPI_CEF_PRINT_HANDLER_CAPI_H_
#define CEF_INCLUDE_CAPI_CEF_PRINT_HANDLER_CAPI_H_
#pragma once

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_browser_capi.h"
#include "include/capi/cef_print_settings_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

///
// Callback structure for asynchronous continuation of print dialog requests.
///
typedef struct _cef_print_dialog_callback_t {
  ///
  // Base structure.
  ///
  cef_base_ref_counted_t base;

  ///
  // Continue printing with the specified |settings|.
  ///
  void(CEF_CALLBACK* cont)(struct _cef_print_dialog_callback_t* self,
                           struct _cef_print_settings_t* settings);

  ///
  // Cancel the printing.
  ///
  void(CEF_CALLBACK* cancel)(struct _cef_print_dialog_callback_t* self);
} cef_print_dialog_callback_t;

///
// Callback structure for asynchronous continuation of print job requests.
///
typedef struct _cef_print_job_callback_t {
  ///
  // Base structure.
  ///
  cef_base_ref_counted_t base;

  ///
  // Indicate completion of the print job.
  ///
  void(CEF_CALLBACK* cont)(struct _cef_print_job_callback_t* self);
} cef_print_job_callback_t;

///
// Implement this structure to handle printing on Linux. Each browser will have
// only one print job in progress at a time. The functions of this structure
// will be called on the browser process UI thread.
///
typedef struct _cef_print_handler_t {
  ///
  // Base structure.
  ///
  cef_base_ref_counted_t base;

  ///
  // Called when printing has started for the specified |browser|. This function
  // will be called before the other OnPrint*() functions and irrespective of
  // how printing was initiated (e.g. cef_browser_host_t::print(), JavaScript
  // window.print() or PDF extension print button).
  ///
  void(CEF_CALLBACK* on_print_start)(struct _cef_print_handler_t* self,
                                     struct _cef_browser_t* browser);

  ///
  // Synchronize |settings| with client state. If |get_defaults| is true (1)
  // then populate |settings| with the default print settings. Do not keep a
  // reference to |settings| outside of this callback.
  ///
  void(CEF_CALLBACK* on_print_settings)(struct _cef_print_handler_t* self,
                                        struct _cef_browser_t* browser,
                                        struct _cef_print_settings_t* settings,
                                        int get_defaults);

  ///
  // Show the print dialog. Execute |callback| once the dialog is dismissed.
  // Return true (1) if the dialog will be displayed or false (0) to cancel the
  // printing immediately.
  ///
  int(CEF_CALLBACK* on_print_dialog)(
      struct _cef_print_handler_t* self,
      struct _cef_browser_t* browser,
      int has_selection,
      struct _cef_print_dialog_callback_t* callback);

  ///
  // Send the print job to the printer. Execute |callback| once the job is
  // completed. Return true (1) if the job will proceed or false (0) to cancel
  // the job immediately.
  ///
  int(CEF_CALLBACK* on_print_job)(struct _cef_print_handler_t* self,
                                  struct _cef_browser_t* browser,
                                  const cef_string_t* document_name,
                                  const cef_string_t* pdf_file_path,
                                  struct _cef_print_job_callback_t* callback);

  ///
  // Reset client state related to printing.
  ///
  void(CEF_CALLBACK* on_print_reset)(struct _cef_print_handler_t* self,
                                     struct _cef_browser_t* browser);

  ///
  // Return the PDF paper size in device units. Used in combination with
  // cef_browser_host_t::print_to_pdf().
  ///
  cef_size_t(CEF_CALLBACK* get_pdf_paper_size)(
      struct _cef_print_handler_t* self,
      int device_units_per_inch);
} cef_print_handler_t;

#ifdef __cplusplus
}
#endif

#endif  // CEF_INCLUDE_CAPI_CEF_PRINT_HANDLER_CAPI_H_
