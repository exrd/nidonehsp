
#ifndef N2R_DAP_INCLUDED
#define N2R_DAP_INCLUDED

#include <stddef.h>
#include <stdint.h>

#include <stdio.h>

#define ZED_NET_STATIC
#define ZED_NET_IMPLEMENTATION
#include "embed/zed_net.h"

#include <nidonehsp.h>

#if !N2_CONFIG_USE_DEBUGGING
#error "n2r_dap requires N2_CONFIG_USE_DEBUGGING"
#endif

// デバッグフック拡張
static const char* N2RI_DAP_SEP = "\r\n";
static const char* N2RI_DAP_TWOSEP = "\r\n\r\n";
static const char* N2RI_DAP_HS = ": ";

typedef struct n2r_dap_t n2r_dap_t;

typedef struct n2r_dap_launch_param_t n2r_dap_launch_param_t;
struct n2r_dap_launch_param_t
{
	n2_str_t program_;
	n2_bool_t no_debug_;
	n2_bool_t stop_on_entry_;
	n2_str_t cwd_;
};

static void n2ri_dap_launch_param_init(n2r_dap_launch_param_t* launch_param)
{
	n2_str_init(&launch_param->program_);
	launch_param->no_debug_ = N2_FALSE;
	launch_param->stop_on_entry_ = N2_FALSE;
	n2_str_init(&launch_param->cwd_);
}

static void n2ri_dap_launch_param_teardown(n2_state_t* s, n2r_dap_launch_param_t* launch_param)
{
	n2_str_teardown(s, &launch_param->program_);
	n2_str_teardown(s, &launch_param->cwd_);
}

typedef struct n2r_dap_stackframeformat_t n2r_dap_stackframeformat_t;
struct n2r_dap_stackframeformat_t
{
	n2_bool_t parameters_;
	n2_bool_t parameterTypes_;
	n2_bool_t parameterNames_;
	n2_bool_t parameterValues_;
	n2_bool_t line_;
	n2_bool_t module_;
	n2_bool_t include_all_;
};

typedef struct n2r_dap_varreq_param_t n2r_dap_varreq_param_t;
struct n2r_dap_varreq_param_t
{
	int start_;
	int count_;
	n2_bool_t include_named_;
	n2_bool_t include_indexed_;
};

static void n2ri_dap_varreq_param_init(n2r_dap_varreq_param_t* varreq)
{
	varreq->start_ = 0;
	varreq->count_ = 0;
	varreq->include_named_ = N2_TRUE;
	varreq->include_indexed_ = N2_TRUE;
}

typedef n2_bool_t (*n2r_dap_staging_cwd_setfunc_t)(n2r_dap_t* dap, const n2_str_t* cwd);
typedef void (*n2r_dap_staging_state_setupfunc_t)(n2r_dap_t* dap, n2_state_config_t* state_config, const n2r_dap_launch_param_t* launch_param);
typedef void (*n2r_dap_staging_state_preloadfunc_t)(n2r_dap_t* dap, n2_state_t* state, const n2r_dap_launch_param_t* launch_param);

#define N2RI_DAP_LOGR(dap, fmt, ...) \
	do { if (dap && dap->enable_dap_logging_) { printf(fmt, ## __VA_ARGS__); } } while (0)
#define N2RI_DAP_LOGL(dap, fmt, ...) \
	do { if (dap && dap->enable_dap_logging_) { printf("[dap] " fmt "\n", ## __VA_ARGS__); } } while (0)

#define N2RI_DAP_TOFRAMEID(fiber_id, callframe_index) \
	N2_SCAST(int, (((fiber_id) << 16) & 0xffff) | ((callframe_index) & 0xffff))

#define N2RI_DAP_FIBERID_FROMFRAMEID(frameid) \
	N2_SCAST(int, ((frameid) >> 16) & 0xffff)

#define N2RI_DAP_CALLFRAMEINDEX_FROMFRAMEID(frameid) \
	N2_SCAST(int, (frameid) & 0xffff)

struct n2r_dap_t
{
	n2_state_t* estate_;
	n2_bool_t serveropen_;
	n2_bool_t servertoclose_;
	zed_net_socket_t serversocket_;
	n2_bool_t remoteopen_;
	n2_bool_t remotetoclose_;
	zed_net_socket_t remotesocket_;
	zed_net_address_t remoteaddr_;
	int check_timeout_usec_;
	size_t accepted_count_;
	n2_bool_t enable_srcref_;
	n2_bool_t enable_varref_;
	n2_bool_t enable_dap_logging_;
	n2_bool_t resolve_to_parent_callframe_on_external_;
	int relative_variabls_line_range_;// don't show Relatives scope if less than 0

	n2_bool_t close_when_dap_disconnected_;

	n2_str_t messagebuf_;
	n2_str_t rcvbuf_;
	int contentsize_;

	int send_sequence_id_;
	n2_str_t responsebuf_;

	n2_bool_t client_connected_;
	n2_str_t client_id_;
	n2_str_t client_name_;
	n2_str_t client_adapter_id_;
	n2_str_t client_locale_;
	n2_bool_t client_line_start_at1_;
	n2_bool_t client_column_start_at1_;
	n2_str_t client_path_format_;
	n2_bool_t client_support_variable_type_;
	n2_bool_t client_support_variable_paging_;
	n2_bool_t client_support_runinterminal_request_;
	n2_bool_t client_support_memory_reference_;
	n2_bool_t client_support_progress_reporting_;
	n2_bool_t client_support_invalidated_event_;

	int srcref_base_;
	int varref_base_;
	int line_base_;
	int column_base_;

	n2_bool_t staging_configuration_done_;
	n2r_dap_staging_cwd_setfunc_t staging_cwd_setfunc_;
	n2r_dap_staging_state_setupfunc_t staging_state_setupfunc_;
	n2r_dap_staging_state_preloadfunc_t staging_state_preloadfunc_;
	n2_str_t staging_startupscript_path_;
	n2_state_t* staging_state_;
	n2_bool_t staging_state_launched_by_dap_;
	n2r_dap_launch_param_t staging_state_launch_param_;
	n2_bool_t staging_continue_requested_;// @todo multi thread support

	void* user_;
};

static void n2ri_dap_stackframeformat_init(n2r_dap_stackframeformat_t* sfformat)
{
	sfformat->parameters_ = N2_FALSE;
	sfformat->parameterTypes_ = N2_FALSE;
	sfformat->parameterNames_ = N2_FALSE;
	sfformat->parameterValues_ = N2_FALSE;
	sfformat->line_ = N2_FALSE;
	sfformat->module_ = N2_FALSE;
	sfformat->include_all_ = N2_FALSE;
}

static void n2ri_dap_print_log_func(void* print_user, n2_state_t* state, n2_fiber_t* fiber, n2_log_level_e log_level, const char* str);

static void n2ri_dap_stackframeformat_fetch(n2r_dap_stackframeformat_t* sfformat, const n2h_datatree_t* argsnode)
{
	//if (!argsnode) { return; }
	sfformat->parameters_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "parameters"), N2_FALSE);
	sfformat->parameterTypes_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "parameterTypes"), N2_FALSE);;
	sfformat->parameterNames_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "parameterNames"), N2_FALSE);;
	sfformat->parameterValues_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "parameterValues"), N2_FALSE);;
	sfformat->line_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "line"), N2_FALSE);;
	sfformat->module_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "module"), N2_FALSE);;
	sfformat->include_all_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "includeAll"), N2_FALSE);;
}

static n2_bool_t n2ri_isstr(const n2_str_t* str, const char* pattern)
{
	return N2_STRNCMP(str->str_, pattern, N2_STRLEN(pattern)) == 0 ? N2_TRUE : N2_FALSE;
}

static n2_bool_t n2ri_datatree_retrieve_str(n2_state_t* estate, n2_str_t* dst, const n2h_datatree_t* datatree, const char* label)
{
	const n2h_datatree_t* found = n2h_datatree_find_bystr(datatree, label);
	if (!found) { return N2_FALSE; }
	if (n2h_datatree_type(found) != N2H_DATATREE_STRING) { return N2_FALSE; }
	const n2_str_t* foundstr = n2h_datatree_peekstr(found);
	N2_ASSERT(foundstr);
	n2_str_copy_to(estate, dst, foundstr);
	return N2_TRUE;
}

typedef struct n2ri_dap_retrieve_callframe_t n2ri_dap_retrieve_callframe_t;
struct n2ri_dap_retrieve_callframe_t
{
	n2_bool_t is_valid_;
	n2_callframe_t* cf_;
};

static n2ri_dap_retrieve_callframe_t n2ri_dap_retrieve_callframe(n2_state_t* state, n2_fiber_t* f, int cfindex)
{
	N2_UNUSE(state);

	n2ri_dap_retrieve_callframe_t res;
	res.is_valid_ = N2_FALSE;
	res.cf_ = NULL;

	const int cfsize = N2_SCAST(int, n2_callframearray_size(f->callframes_));

	if (f && cfindex >= 0 && cfindex < (cfsize + 1/*current*/))
	{
		const int real_cfindex = cfsize - cfindex;// 後ろから数える
		//const int real_cfindex = cfindex - 1;// 前から数える
		n2_callframe_t* cf = cfindex == 0 ? NULL : n2_callframearray_peek(f->callframes_, real_cfindex);
		res.is_valid_ = N2_TRUE;
		res.cf_ = cf;
	}
	return res;
}

static void n2ri_dap_setup_debughook(n2r_dap_t* dap, n2_debughook_t* debughook);

static n2_bool_t n2ri_dap_push_message(n2r_dap_t* dap, const char* data, size_t data_length)
{
	if (!data || data_length <= 0) { return N2_FALSE; }
	// ヘッダを詰める
	n2_str_append_fmt(dap->estate_, &dap->responsebuf_, "Content-Length%s%zu%s", N2RI_DAP_HS, data_length, N2RI_DAP_SEP);
	// コンテンツとの境目
	n2_str_append(dap->estate_, &dap->responsebuf_, N2RI_DAP_SEP, SIZE_MAX);
	// コンテンツを詰める
	n2_str_append(dap->estate_, &dap->responsebuf_, data, data_length);
	//N2RI_DAP_LOGL(dap, "push message(%.*s)", N2_SCAST(int, N2_MIN(data_length, 128)), data);
	N2RI_DAP_LOGL(dap, "push message ALL(%.*s)", N2_SCAST(int, data_length), data);
	return N2_TRUE;
}

static int n2ri_dap_next_seq_id(const n2r_dap_t* dap)
{
	return dap->send_sequence_id_;
}

static int n2ri_dap_push_message_seq_header(n2r_dap_t* dap, n2_state_t* s, n2_str_t* t)
{
	n2_str_append_fmt(s, t, "\"seq\": %d\n", dap->send_sequence_id_);
	return dap->send_sequence_id_++;
}

#define N2RI_DAP_TMESSAGE_BEGIN(dap) \
	n2_state_t* s = dap->estate_; \
	n2_str_t tmpstr; \
	n2_str_init(&tmpstr); \
	n2_str_set_expand_step(&tmpstr, 1 * 1024); \
	n2_str_t* t = &tmpstr

#define N2RI_DAP_TMESSAGE_END(dap) \
	n2_str_teardown(s, &tmpstr)

#define N2RI_DAP_MESSAGE_OPEN(dap) \
	N2RI_DAP_TMESSAGE_BEGIN(dap); \
	n2_str_append(s, t, "{\n", SIZE_MAX)

#define N2RI_DAP_MESSAGE_ENTER(dap) \
	N2RI_DAP_MESSAGE_OPEN(dap)

#define N2RI_DAP_MESSAGE_CLOSE(dap) \
	n2_str_append(s, t, "}", SIZE_MAX)

#define N2RI_DAP_MESSAGE_LEAVE(dap) \
	N2RI_DAP_MESSAGE_CLOSE(dap); \
	const n2_bool_t res = n2ri_dap_push_message(dap, tmpstr.str_, tmpstr.size_); \
	N2RI_DAP_TMESSAGE_END(dap)

static int n2ri_dap_push_request_header(n2_state_t* s, n2_str_t* t, n2r_dap_t* dap, const char* command, size_t command_length)
{
	const int seq = n2ri_dap_push_message_seq_header(dap, s, t);
	n2_str_append_fmt(s, t, ", \"type\": \"request\"\n");
	if (command)
	{
		if (command_length == SIZE_MAX) { command_length = N2_STRLEN(command); }
		n2_str_append_fmt(s, t, ", \"command\": \"%.*s\"\n", command_length, command);
	}
	return seq;
}

static void n2ri_dap_push_response_header(n2_state_t* s, n2_str_t* t, n2r_dap_t* dap, int rseq, n2_bool_t success, const char* command, size_t command_length, const char* message)
{
	N2_UNUSE(dap);
	n2_str_append_fmt(s, t, "\"request_seq\": %d\n", rseq);
	n2_str_append_fmt(s, t, ", \"type\": \"response\"\n");
	n2_str_append_fmt(s, t, ", \"success\": %s\n", success ? "true" : "false");
	if (command)
	{
		if (command_length == SIZE_MAX) { command_length = N2_STRLEN(command); }
		n2_str_append_fmt(s, t, ", \"command\": \"%.*s\"\n", command_length, command);
	}
	if (message)
	{
		n2_str_append_fmt(s, t, ", \"message\": \"%s\"", message);
	}
}

static void n2ri_dap_push_event_header(n2_state_t* s, n2_str_t* t, n2r_dap_t* dap, const char* ev, size_t ev_length)
{
	N2_UNUSE(dap);
	n2_str_append_fmt(s, t, "\"type\": \"event\"\n");
	if (ev_length == SIZE_MAX) { ev_length = N2_STRLEN(ev); }
	n2_str_append_fmt(s, t, ", \"event\": \"%.*s\"\n", ev_length, ev);
}

static n2_bool_t n2ri_dap_push_event_template(n2r_dap_t* dap, const char* ev, size_t ev_length)
{
	N2RI_DAP_MESSAGE_ENTER(dap);
	{
		n2ri_dap_push_event_header(s, t, dap, ev, ev_length);
	}
	N2RI_DAP_MESSAGE_LEAVE(dap);
	return res;
}

static n2_bool_t n2ri_dap_push_response_template(n2r_dap_t* dap, int rseq, n2_bool_t success, const n2_str_t* command, const char* message)
{
	N2RI_DAP_MESSAGE_ENTER(dap);
	{
		n2ri_dap_push_response_header(s, t, dap, rseq, success, command->str_, command->size_, message);
	}
	N2RI_DAP_MESSAGE_LEAVE(dap);
	return res;
}

static void n2ri_dap_push_source_content(n2_state_t* s, n2_str_t* t, n2r_dap_t* dap, n2_state_t* state, const n2_sourcecode_t* sourcecode)
{
	const n2_sourcefile_t* sourcefile = sourcecode->sourcefile_;
	n2_str_append_fmt(s, t, "\"name\": \"%s\"\n", sourcecode->package_.str_);
	if (sourcefile)
	{
		if (sourcefile->src_resolved_filepath_escaped_.size_ > 0) { n2_str_append_fmt(s, t, ", \"path\": \"%s\"\n", sourcefile->src_resolved_filepath_escaped_.str_); }
		if (dap->enable_srcref_) { n2_str_append_fmt(s, t, ", \"sourceReference\": %d\n", sourcefile->id_ + dap->srcref_base_); }
	}
	n2_str_append_fmt(s, t, ", \"presentationHint\": \"normal\"\n");
	//n2_str_append_fmt(s, t, ", \"origin\": \"\"\n");
	if (sourcecode->parent_sourcecode_)
	{
		n2_str_append_fmt(s, t, ", \"sources\": [\n");
		n2_str_append_fmt(s, t, "{\n");
		n2ri_dap_push_source_content(s, t, dap, state, sourcecode->parent_sourcecode_);
		n2_str_append_fmt(s, t, "}\n");
		n2_str_append_fmt(s, t, "]\n");
	}
	//n2_str_append_fmt(s, t, ", \"adapterDate\": \"\"\n");
	//n2_str_append_fmt(s, t, ", \"checksums\": []\n");
}

static n2_bool_t n2ri_dap_push_thread_stacktrace(n2_state_t* s, n2_str_t* t, n2r_dap_t* dap, n2_state_t* state, n2_fiber_t* f, int start_frame, int levels, const n2r_dap_stackframeformat_t* sfformat)
{
	N2_UNUSE(sfformat);

	int total_stack_frame = 0;

	n2_str_append_fmt(s, t, "\"stackFrames\": [\n");
	if (f)
	{
		int cfsize = N2_SCAST(int, n2_callframearray_size(f->callframes_));
		total_stack_frame = cfsize + 1/*current*/;
		if (levels <= 0) { levels = total_stack_frame; }// 全取得
		for (int i = 0; i < levels; ++i)
		{
			const int cfindex = start_frame + i;
			const n2ri_dap_retrieve_callframe_t cfr = n2ri_dap_retrieve_callframe(state, f, cfindex);
			if (!cfr.is_valid_) { continue; }

			const n2_callframe_t* cf = cfr.cf_;
			const n2_func_t* cffunc = NULL;
			const n2_label_t* cflabel = NULL;
			const char* cfname = NULL;
			int cfop = -1;
			if (cf)
			{
				cfop = cf->caller_pc_;
				cffunc = cf->caller_function_;
				cflabel = cf->caller_label_;
			}
			else
			{
				cfop = f->op_pc_;
				cffunc = f->callstate_.func_;
				cflabel = f->callstate_.label_;
			}

			cfname = "main";
			if (cffunc) { cfname = cffunc->name_; }
			if (cflabel) { cfname = cflabel->name_; }

			int use_cfindex = cfindex;
			while (cfop < 0 && dap->resolve_to_parent_callframe_on_external_)
			{
				++use_cfindex;
				const n2ri_dap_retrieve_callframe_t ucfr = n2ri_dap_retrieve_callframe(state, f, use_cfindex);
				if (!ucfr.is_valid_) { break; }
				cfop = ucfr.cf_ ? ucfr.cf_->caller_pc_ : f->op_pc_;
			}

			const n2_codeline_t* cfcodeline = n2_codeimage_find_codeline_from_pc(f->environment_->codeimage_, cfop);

			if (i > 0) { n2_str_append_fmt(s, t, ", "); }
			n2_str_append_fmt(s, t, "{\n");
			n2_str_append_fmt(s, t, "\"id\": %d\n", N2RI_DAP_TOFRAMEID(f->id_, cfindex));
			n2_str_append_fmt(s, t, ", \"name\": \"%s\"\n", cfname ?  cfname : "<unknown>");
			if (cfcodeline && cfcodeline->sourcecode_)
			{
				n2_str_append_fmt(s, t, ", \"source\": {\n");
				n2ri_dap_push_source_content(s, t, dap, state, cfcodeline->sourcecode_);
				n2_str_append_fmt(s, t, "}\n");
			}

			const int line = cfcodeline ? cfcodeline->line_ + dap->line_base_ : -1;
			n2_str_append_fmt(s, t, ", \"line\": %d\n", line);

			// とりあえず行全体にする
#if 1
			n2_str_append_fmt(s, t, ", \"column\": %d\n", 0);
#else
			n2_str_append_fmt(s, t, ", \"column\": %d\n", 0 + dap->column_base_);
			n2_str_append_fmt(s, t, ", \"endLine\": %d\n", line);
			//n2_str_append_fmt(s, t, ", \"endColumn\": -1\n");
			if (cfcodeline && cfcodeline->line_head_)
			{
				const int end_column = n2_plstr_search_pattern(cfcodeline->line_head_, "\n", 1);
				if (end_column >= 0)
				{
					n2_str_append_fmt(s, t, ", \"endColumn\": %d\n", end_column + dap->column_base_);
				}
			}
#endif

			//n2_str_append_fmt(s, t, ", \"canRestart\": false\n");
			//n2_str_append_fmt(s, t, ", \"instructionPointerReference\": \"\"\n");
			//n2_str_append_fmt(s, t, ", \"moduleId\": -1\n");
			//n2_str_append_fmt(s, t, ", \"presentationHint\": \"normal\"\n");
			n2_str_append_fmt(s, t, "}\n");
		}
	}
	n2_str_append_fmt(s, t, "]\n");
	n2_str_append_fmt(s, t, ", \"totalFrames\": %d\n", total_stack_frame);

	return N2_TRUE;
}

static n2_bool_t n2ri_dap_push_response_initialize(n2r_dap_t* dap, int rseq)
{
	N2RI_DAP_MESSAGE_ENTER(dap);
	{
		n2ri_dap_push_response_header(s, t, dap, rseq, N2_TRUE, "initialize", SIZE_MAX, NULL);
		n2_str_append_fmt(s, t, ", \"body\": {\n");
		{
			// capabilities
			n2_str_append_fmt(s, t, "\"supportsConfigurationDoneRequest\": true\n");
			//n2_str_append_fmt(s, t, ", \", supportsFunctionBreakpoints\": true\n");
			///n2_str_append_fmt(s, t, ", \"supportsConditionalBreakpoints\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsHitConditionalBreakpoints\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsEvaluateForHovers\": true\n");
			///n2_str_append_fmt(s, t, ", \"exceptionBreakpointFilters\": []\n");
			///n2_str_append_fmt(s, t, ", \"supportsStepBack\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsSetVariable\": true\n");
			///n2_str_append_fmt(s, t, ", \"supportsRestartFrame\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsGotoTargetsRequest\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsStepInTargetsRequest\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsCompletionsRequest\": true\n");
			//n2_str_append_fmt(s, t, ", \"completionTriggerCharacters\": []\n");
			//n2_str_append_fmt(s, t, ", \"supportsModulesRequest\": true\n");
			//n2_str_append_fmt(s, t, ", \"additionalModuleColumns\": []\n");
			//n2_str_append_fmt(s, t, ", \"supportsRestartRequest\": true\n");
			///n2_str_append_fmt(s, t, ", \"supportsExceptionOptions\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsValueFormattingOptions\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsExceptionInfoRequest\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportTerminateDebuggee\": true\n");
			n2_str_append_fmt(s, t, ", \"supportsDelayedStackTraceLoading\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsLoadedSourcesRequest\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsLogPoints\": true\n");
			///n2_str_append_fmt(s, t, ", \"supportsTerminateThreadsRequest\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsSetExpression\": true\n");
			n2_str_append_fmt(s, t, ", \"supportsTerminateRequest\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsDataBreakpoints\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsReadMemoryRequest\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsDisassembleRequest\": true\n");
			///n2_str_append_fmt(s, t, ", \"supportsCancelRequest\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsBreakpointLocationsRequest\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsClipboardContext\": true\n");
			n2_str_append_fmt(s, t, ", \"supportsSteppingGranularity\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsInstructionBreakpoints\": true\n");
			//n2_str_append_fmt(s, t, ", \"supportsExceptionFilterOptions\": true\n");
		}
		n2_str_append_fmt(s, t, "}\n");
	}
	N2RI_DAP_MESSAGE_LEAVE(dap);
	return res;
}

static n2_bool_t n2ri_dap_push_event_breakstopped(n2r_dap_t* dap, n2_fiber_t* f, n2_debughook_stop_reason_e reason, const char* description)
{
	if (reason == N2_DEBUGHOOK_STOP_REASON_ASSERT && !description) { description = "ASSERTに失敗しました。"; }

	N2RI_DAP_MESSAGE_ENTER(dap);
	{
		n2ri_dap_push_event_header(s, t, dap, "stopped", SIZE_MAX);
		n2_str_append_fmt(s, t, ", \"body\": {\n");
		{
			n2_str_append_fmt(s, t, "\"threadId\": %d\n", f->id_);
			n2_str_append_fmt(s, t, ", \"reason\": \"%s\"\n", 
				reason == N2_DEBUGHOOK_STOP_REASON_ASSERT ? "exception" : 
				reason == N2_DEBUGHOOK_STOP_REASON_BREAKPOINT ? "breakpoint" : 
				reason == N2_DEBUGHOOK_STOP_REASON_STEP ? "step" : 
				reason == N2_DEBUGHOOK_STOP_REASON_ERROR ? "exception" : 
				"pause"
			);
			if (description) { n2_str_append_fmt(s, t, ", \"description\": \"%s\"\n", description); n2_str_append_fmt(s, t, ", \"text\": \"%s\"\n", description); }
			const n2_bool_t preserve_focus = reason == N2_DEBUGHOOK_STOP_REASON_NONE || reason == N2_DEBUGHOOK_STOP_REASON_PAUSE;
			n2_str_append_fmt(s, t, ", \"preserveFocusHint\": %s\n", preserve_focus ? "true" : "false");
			//n2_str_append_fmt(s, t, ", \"text\": \"\"\n");
			//n2_str_append_fmt(s, t, ", \"allThreadsStopped\": true\n");
		}
		n2_str_append_fmt(s, t, "}\n");
	}
	N2RI_DAP_MESSAGE_LEAVE(dap);
	return res;
}

static n2_bool_t n2ri_dap_push_event_output(n2r_dap_t* dap, const char* message, n2_fiber_t* f, const char* category, const char* group)
{
	N2_UNUSE(f);
	N2RI_DAP_MESSAGE_ENTER(dap);
	{
		n2ri_dap_push_event_header(s, t, dap, "output", SIZE_MAX);
		n2_str_append_fmt(s, t, ", \"body\": {\n");
		{
			n2_str_t tstr;
			n2_str_init(&tstr);
			n2_str_escaped_to(s, &tstr, message, SIZE_MAX, N2_STR_ESCAPE_FLAG_JSON);
			n2_str_append_fmt(s, t, "\"output\": \"%s\\n\"\n", tstr.str_);
			if (category) { n2_str_append_fmt(s, t, ", \"category\": \"%s\"\n", category); }
			if (group) { n2_str_append_fmt(s, t, ", \"group\": \"%s\"\n", group); }
			if (f)
			{
				n2_pc_t oppc = f->op_pc_;
				if (oppc < 0)
				{
					// outputイベント時は１個上まで見る、logmesのための特殊対応
					const n2_callframe_t* cf = n2_callframearray_peek(f->callframes_, -1);
					if (cf) { oppc = cf->caller_pc_; }
				}

				const n2_codeline_t* cfcodeline = n2_codeimage_find_codeline_from_pc(f->environment_->codeimage_, oppc);

				if (cfcodeline && cfcodeline->sourcecode_)
				{
					n2_str_append_fmt(s, t, ", \"source\": {\n");
					n2ri_dap_push_source_content(s, t, dap, dap->staging_state_, cfcodeline->sourcecode_);
					n2_str_append_fmt(s, t, "}\n");
				}
				n2_str_append_fmt(s, t, ", \"line\": %d\n", cfcodeline ? cfcodeline->line_ + dap->line_base_ : -1);
				n2_str_append_fmt(s, t, ", \"column\": %d\n", 0 + dap->column_base_);
			}
			n2_str_teardown(s, &tstr);
		}
		n2_str_append_fmt(s, t, "}\n");
	}
	N2RI_DAP_MESSAGE_LEAVE(dap);
	return res;
}

static void n2ri_dap_push_thread(n2_state_t* s, n2_str_t* t, n2r_dap_t* dap, n2_state_t* state, n2_fiber_t* f)
{
	N2_UNUSE(dap);
	N2_UNUSE(state);
	n2_str_append_fmt(s, t, "{\n");
	{
		n2_str_append_fmt(s, t, "\"id\": %d\n", f->id_);
		n2_str_append_fmt(s, t, ", \"name\": \"%s\"\n", f->name_.str_);
	}
	n2_str_append_fmt(s, t, "}\n");
}

static void n2ri_dap_push_threads(n2_state_t* s, n2_str_t* t, n2r_dap_t* dap, n2_state_t* state)
{
	n2_str_append_fmt(s, t, "\"threads\": [\n");
	if (state)
	{
		// @todo multi fiber
		n2ri_dap_push_thread(s, t, dap, state, state->main_fiber_);
	}
	n2_str_append_fmt(s, t, "]\n");
}

static n2_bool_t n2r_dap_handle_source(n2r_dap_t* dap, int seq, const n2_str_t* commandstr, const n2h_datatree_t* argsnode)
{
	n2_state_t* es = dap->estate_;
	// 解析
	n2_bool_t success = N2_TRUE;
	n2_str_t emessage; n2_str_init(&emessage);
	if (dap->staging_state_)
	{
		n2_state_t* state = dap->staging_state_;
		n2_codeimage_t* codeimage = state->environment_->codeimage_;

		const n2h_datatree_t* sourcenode = n2h_datatree_find_bystr(argsnode, "source");
		const n2_str_t* sourcefilepath = n2h_datatree_peekstr(n2h_datatree_find_bystr(sourcenode, "path"));
		int sourcereference = N2_SCAST(int, n2h_datatree_asint(n2h_datatree_find_bystr(sourcenode, "sourceReference"), -1)) - dap->srcref_base_;
		if (sourcereference < 0) { sourcereference = N2_SCAST(int, n2h_datatree_asint(n2h_datatree_find_bystr(argsnode, "sourceReference"), -1)) - dap->srcref_base_; }// 直下のsourceReferenceにfallback

		// 該当するsourcefileを検索
		const n2_sourcefilearray_t* sourcefiles = codeimage->sourcefiles_;
		const n2_sourcefile_t* sourcefile = NULL;
		if (sourcefiles)
		{
			// sourceReferenceから一意に検索
			if (!sourcefile && sourcereference >= 0)
			{
				sourcefile = n2_sourcefilearray_peekcv(sourcefiles, sourcereference, NULL);
			}
			// pathから線形検索
			if (!sourcefile && sourcefilepath)
			{
				for (size_t i = 0, l = n2_sourcefilearray_size(sourcefiles); i < l; ++i)
				{
					const n2_sourcefile_t* psourcefile = *n2_sourcefilearray_peekc(sourcefiles, N2_SCAST(int, i));
					if (n2_path_compare(&psourcefile->src_resolved_filepath_, sourcefilepath) == 0)
					{
						sourcefile = psourcefile;
						break;
					}
				}
			}
		}
		if (sourcefile && n2_sourcecodeptrarray_size(&sourcefile->sourcecodeptrs_) > 0)
		{
			// プリプロセス済みのものは異なっていても、プリプロセス前の中身は同じなのでそれを使う
			const n2_sourcecode_t* sourcecode = n2_sourcecodeptrarray_peekcv(&sourcefile->sourcecodeptrs_, 0, NULL);
			N2_ASSERT(sourcecode);
			N2RI_DAP_TMESSAGE_BEGIN(dap);
			n2_str_append(s, t, "{\n", SIZE_MAX);
			{
				n2ri_dap_push_response_header(s, t, dap, seq, N2_TRUE, commandstr->str_, commandstr->size_, NULL);
				n2_str_append_fmt(s, t, ", \"body\": {\n");
				{
					n2_str_t content_escaped;
					n2_str_init(&content_escaped);
					n2_str_escaped_to(s, &content_escaped, sourcecode->src_script_.str_, sourcecode->src_script_.size_, N2_STR_ESCAPE_FLAG_JSON);
					n2_str_append_fmt(s, t, "\"content\": \"%s\"\n", content_escaped.str_);
					//n2_str_append_fmt(s, t, ", \"mimeType\": \"text/plain\"\n");
					n2_str_teardown(s, &content_escaped);
				}
				n2_str_append_fmt(s, t, "}\n");
			}
			n2_str_append(s, t, "}\n", SIZE_MAX);
			if (!n2ri_dap_push_message(dap, t->str_, t->size_)) { success = N2_FALSE; }
			N2RI_DAP_TMESSAGE_END(dap);
		}
		else
		{
			success = N2_FALSE;
			n2_str_fmt_to(es, &emessage, "Failed parsing arguments or source(%.*s) not found.", sourcefilepath ? sourcefilepath->size_ : 0, sourcefilepath ? sourcefilepath->str_ : "<unknown>");
		}
	}
	else
	{
		success = N2_FALSE;
		n2_str_set(es, &emessage, "No staging state to source.", SIZE_MAX);
	}
	// エラー時のレスポンス
	n2_bool_t res = N2_TRUE;
	if (!success && !n2ri_dap_push_response_template(dap, seq, success, commandstr, emessage.str_)) { res = N2_FALSE; }
	n2_str_teardown(es, &emessage);
	return res;
}

static n2_bool_t n2r_dap_handle_threads(n2r_dap_t* dap, int seq, const n2_str_t* commandstr)
{
	n2_state_t* es = dap->estate_;
	// 解析
	n2_str_t emessage; n2_str_init(&emessage);
	n2_bool_t res = N2_TRUE;
	if (dap->staging_state_)
	{
		N2RI_DAP_TMESSAGE_BEGIN(dap);
		n2_str_append(s, t, "{\n", SIZE_MAX);
		{
			n2ri_dap_push_response_header(s, t, dap, seq, N2_TRUE, commandstr->str_, commandstr->size_, NULL);
			n2_str_append_fmt(s, t, ", \"body\": {\n");
			{
				n2ri_dap_push_threads(s, t, dap, dap->staging_state_);
			}
			n2_str_append_fmt(s, t, "}\n");
		}
		n2_str_append(s, t, "}\n", SIZE_MAX);
		if (!n2ri_dap_push_message(dap, t->str_, t->size_)) { res = N2_FALSE; }
		N2RI_DAP_TMESSAGE_END(dap);
	}
	else
	{
		res = N2_FALSE;
		n2_str_set(es, &emessage, "no staging state. not launched yet", SIZE_MAX);
		if (!n2ri_dap_push_response_template(dap, seq, N2_FALSE, commandstr, emessage.str_)) { res = N2_FALSE; }
	}
	// 解放
	n2_str_teardown(es, &emessage);
	return res;
}

static n2_bool_t n2r_dap_handle_stack_trace(n2r_dap_t* dap, int seq, const n2_str_t* commandstr, const n2h_datatree_t* argsnode)
{
	n2_state_t* es = dap->estate_;
	int thread_id = -1;
	int start_frame = 0;
	int levels = 0;
	n2r_dap_stackframeformat_t sfformat;
	n2ri_dap_stackframeformat_init(&sfformat);
	if (argsnode && n2h_datatree_type(argsnode) == N2H_DATATREE_MAP)
	{
		thread_id = N2_SCAST(int, n2h_datatree_asint(n2h_datatree_find_bystr(argsnode, "threadId"), -1));
		start_frame = N2_SCAST(int, n2h_datatree_asint(n2h_datatree_find_bystr(argsnode, "startFrame"), 0));
		levels = N2_SCAST(int, n2h_datatree_asint(n2h_datatree_find_bystr(argsnode, "levels"), 0));
		n2ri_dap_stackframeformat_fetch(&sfformat, n2h_datatree_find_bystr(argsnode, "format"));
	}
	// 解析
	n2_str_t emessage; n2_str_init(&emessage);
	n2_bool_t res = N2_TRUE;
	if (dap->staging_state_)
	{
		n2_state_t* state = dap->staging_state_;
		n2_fiber_t* f = n2_state_find_fiber(state, thread_id);
		if (f)
		{
			N2RI_DAP_TMESSAGE_BEGIN(dap);
			n2_str_append(s, t, "{\n", SIZE_MAX);
			{
				n2ri_dap_push_response_header(s, t, dap, seq, N2_TRUE, commandstr->str_, commandstr->size_, NULL);
				n2_str_append_fmt(s, t, ", \"body\": {\n");
				{
					n2ri_dap_push_thread_stacktrace(s, t, dap, state, f, start_frame, levels, &sfformat);
				}
				n2_str_append_fmt(s, t, "}\n");
			}
			n2_str_append(s, t, "}\n", SIZE_MAX);
			if (!n2ri_dap_push_message(dap, t->str_, t->size_)) { res = N2_FALSE; }
			N2RI_DAP_TMESSAGE_END(dap);
		}
		else
		{
			res = N2_FALSE;
			n2_str_fmt_to(es, &emessage, "no thread corresponding to threadId(%d)", thread_id);
			if (!n2ri_dap_push_response_template(dap, seq, N2_FALSE, commandstr, emessage.str_)) { res = N2_FALSE; }
		}
	}
	else
	{
		res = N2_FALSE;
		n2_str_set(es, &emessage, "no staging state. not launched yet", SIZE_MAX);
		if (!n2ri_dap_push_response_template(dap, seq, N2_FALSE, commandstr, emessage.str_)) { res = N2_FALSE; }
	}
	// 解放
	n2_str_teardown(es, &emessage);
	return res;
}

static void n2ri_dap_push_null_variables_reference(n2_state_t* s, n2_str_t* t, n2r_dap_t* dap)
{
	N2_UNUSE(dap);
	n2_str_append_fmt(s, t, "\"variablesReference\": %d\n", 0);
}

static n2_bool_t n2ri_dap_push_variables_reference(n2_state_t* s, n2_str_t* t, n2r_dap_t* dap, n2_state_t* state, const n2_debugvariable_t* debugvar)
{
	N2_UNUSE(dap);
	N2_UNUSE(state);
	if (!debugvar) { return N2_FALSE; }

	size_t named_variables = 0;
	size_t indexed_variables = 0;

	switch (debugvar->type_)
	{
	case N2_DEBUGVARIABLE_ENVIRONMENT:
		{
			const n2_environment_t* e = debugvar->v_.environment_;
			named_variables = n2_vartable_size_named(e->vartable_);
		}
		break;
	case N2_DEBUGVARIABLE_SYSVAR:
		{
			const n2_fiber_t* f = debugvar->v_.sysvar_.fiber_;
			named_variables = N2_MAX_SYSVAR + N2_SCAST(int, n2_sysvarexarray_size(f->environment_->sysvar_ex_));
		}
		break;
	case N2_DEBUGVARIABLE_FIBER:
		{
			// top of the callstack
			const n2_fiber_t* f = debugvar->v_.fiber_;
			if (f->callstate_.func_)
			{
				named_variables = f->callstate_.debugvarargs_ ? n2_debugvararray_size(f->callstate_.debugvarargs_) : f->callstate_.ordered_arg_num_;// @todo キーワード引数もスカされたときに考慮しておくべき？
			}
		}
		break;
	case N2_DEBUGVARIABLE_FIBER_CALLFRAME:
		{
			const n2_fiber_t* f = debugvar->v_.fiber_cf_.fiber_;
			const n2_callframe_t* cf = debugvar->v_.fiber_cf_.callframe_index_ >= 0 ? n2_callframearray_peek(f->callframes_, debugvar->v_.fiber_cf_.callframe_index_) : NULL;
			if (cf && cf->caller_function_)
			{
				named_variables = cf->debugvarargs_ ? n2_debugvararray_size(cf->debugvarargs_) : cf->ordered_arg_num_;// @todo キーワード引数もスカされたときに考慮しておくべき？
			}
		}
		break;
	case N2_DEBUGVARIABLE_FIBER_RELATIVES:
		{
			n2_fiber_t* f = debugvar->v_.fiber_;
			n2_debugvarrelatives_update(state, f->environment_, &f->debugvarrelatives_, &f->debugvarrelpc_, f->op_pc_, dap->relative_variabls_line_range_);
			named_variables = n2_intset_size(&f->debugvarrelatives_);
		}
		break;
	case N2_DEBUGVARIABLE_FIBER_CALLFRAME_RELATIVES:
		{
			const n2_fiber_t* f = debugvar->v_.fiber_cf_.fiber_;
			n2_callframe_t* cf = debugvar->v_.fiber_cf_.callframe_index_ >= 0 ? n2_callframearray_peek(f->callframes_, debugvar->v_.fiber_cf_.callframe_index_) : NULL;
			if (cf)
			{
				n2_debugvarrelatives_update(state, f->environment_, &cf->debugvarrelatives_, &cf->debugvarrelpc_, cf->caller_pc_, dap->relative_variabls_line_range_);
				named_variables = n2_intset_size(&cf->debugvarrelatives_);
			}
		}
		break;
	case N2_DEBUGVARIABLE_VARIABLE_ROOT:
		{
			const n2_variable_t* var = debugvar->v_.var_root_;
			indexed_variables = var->length_[0];
		}
		break;
	case N2_DEBUGVARIABLE_VARIABLE_DIMENSION:
		{
			const n2_variable_t* var = debugvar->v_.var_dimension_.var_;
			indexed_variables = var->length_[debugvar->v_.var_dimension_.dimension_index_];
		}
		break;
	default:
		break;
	}

	const n2_bool_t is_structured = named_variables > 0 || indexed_variables > 0;
	n2_str_append_fmt(s, t, "\"variablesReference\": %d\n", is_structured ? N2_SCAST(int, debugvar->id_) + dap->varref_base_ : 0);
	n2_str_append_fmt(s, t, ", \"namedVariables\": %zu\n", named_variables);
	n2_str_append_fmt(s, t, ", \"indexedVariables\": %zu\n", indexed_variables);
	return N2_TRUE;
}

static void n2ri_dap_push_variable_content(n2_state_t* s, n2_str_t* t, n2r_dap_t* dap, n2_state_t* state, const n2_debugvariable_t* debugvar)
{
	n2_str_append_fmt(s, t, "{\n");
	if (debugvar)
	{
		n2_str_t tvstr;
		n2_str_init(&tvstr);
		n2_str_t tvestr;
		n2_str_init(&tvestr);

		switch (debugvar->type_)
		{
		case N2_DEBUGVARIABLE_ENVIRONMENT:
			{
				n2_str_append_fmt(s, t, "\"name\": \"environment(globals)\"\n");
				n2_str_append_fmt(s, t, ", \"type\": \"environment\"\n");
				n2_str_append_fmt(s, t, ", \"value\": \"(no value)\"\n");
				n2_str_append_fmt(s, t, ", ");
				n2ri_dap_push_variables_reference(s, t, dap, state, debugvar);
			}
			break;
		case N2_DEBUGVARIABLE_SYSVAR:
			{
				n2_str_append_fmt(s, t, "\"name\": \"sysvar\"\n");
				n2_str_append_fmt(s, t, ", \"type\": \"sysvar\"\n");
				n2_str_append_fmt(s, t, ", \"value\": \"(no value)\"\n");
				n2_str_append_fmt(s, t, ", ");
				n2ri_dap_push_variables_reference(s, t, dap, state, debugvar);
			}
			break;
		case N2_DEBUGVARIABLE_SYSVAR_ELEMENT:
			{
				n2_fiber_t* f = debugvar->v_.sysvar_element_.fiber_;
				const int sysvar_index = debugvar->v_.sysvar_element_.sysvar_index_;
				if (sysvar_index < N2_MAX_SYSVAR)
				{
					const n2_sysvar_e sysvar = N2_SCAST(n2_sysvar_e, sysvar_index);
					n2_str_append_fmt(s, t, "\"name\": \"%s\"\n", n2_sysvar_name(sysvar, NULL));
					n2_sysvar_inspect(s, &tvstr, &tvestr, sysvar, f);
					n2_str_append_fmt(s, t, ", \"type\": \"%s\"\n", tvestr.str_);
					n2_str_escaped_to(s, &tvestr, tvstr.str_, tvstr.size_, N2_STR_ESCAPE_FLAG_JSON);
					n2_str_append_fmt(s, t, ", \"value\": \"%s\"\n", tvestr.str_);
				}
				else
				{
					const int sysvarex_index = sysvar_index - N2_MAX_SYSVAR;
					n2_sysvar_ex_t* sysvarex = n2_sysvarexarray_peek(f->environment_->sysvar_ex_, sysvarex_index);
					if (sysvarex)
					{
						n2_str_append_fmt(s, t, "\"name\": \"%s\"\n", sysvarex->name_);
						if (sysvarex->inspect_)
						{
							sysvarex->inspect_(s, f, &tvstr, &tvestr, sysvarex);
							n2_str_append_fmt(s, t, ", \"type\": \"%s\"\n", tvestr.str_);
							n2_str_escaped_to(s, &tvestr, tvstr.str_, tvstr.size_, N2_STR_ESCAPE_FLAG_JSON);
							n2_str_append_fmt(s, t, ", \"value\": \"%s\"\n", tvestr.str_);
						}
					}
				}
				n2_str_append_fmt(s, t, ", ");
				n2ri_dap_push_variables_reference(s, t, dap, state, debugvar);
			}
			break;
		case N2_DEBUGVARIABLE_FIBER:
			{
				n2_fiber_t* f = debugvar->v_.fiber_;
				n2_str_append_fmt(s, t, "\"name\": \"fiber(%d:%s)\"\n", f->id_, f->name_);
				n2_str_append_fmt(s, t, ", \"type\": \"fiber\"\n");
				n2_str_append_fmt(s, t, ", \"value\": \"(%p)\"\n", f);
				n2_str_append_fmt(s, t, ", ");
				n2ri_dap_push_variables_reference(s, t, dap, state, debugvar);
			}
			break;
		case N2_DEBUGVARIABLE_FIBER_CALLFRAME:
			{
				n2_str_append_fmt(s, t, "\"name\": \"callFrame(%d)\"\n", debugvar->v_.fiber_cf_.callframe_index_);
				n2_str_append_fmt(s, t, ", \"type\": \"callFrame\"\n");
				n2_str_append_fmt(s, t, ", \"value\": \"(no value)\"\n");
				n2_str_append_fmt(s, t, ", ");
				n2ri_dap_push_variables_reference(s, t, dap, state, debugvar);
			}
			break;
		case N2_DEBUGVARIABLE_FIBER_RELATIVES:
			{
				n2_fiber_t* f = debugvar->v_.fiber_;
				n2_str_append_fmt(s, t, "\"name\": \"fiberRels(%d:%s)\"\n", f->id_, f->name_);
				n2_str_append_fmt(s, t, ", \"type\": \"fiber\"\n");
				n2_str_append_fmt(s, t, ", \"value\": \"(%p)\"\n", f);
				n2_str_append_fmt(s, t, ", ");
				n2ri_dap_push_variables_reference(s, t, dap, state, debugvar);
			}
			break;
		case N2_DEBUGVARIABLE_FIBER_CALLFRAME_RELATIVES:
			{
				n2_str_append_fmt(s, t, "\"name\": \"callFrameRels(%d)\"\n", debugvar->v_.fiber_cf_.callframe_index_);
				n2_str_append_fmt(s, t, ", \"type\": \"callFrame\"\n");
				n2_str_append_fmt(s, t, ", \"value\": \"(no value)\"\n");
				n2_str_append_fmt(s, t, ", ");
				n2ri_dap_push_variables_reference(s, t, dap, state, debugvar);
			}
			break;
		case N2_DEBUGVARIABLE_VARIABLE_ROOT:
		case N2_DEBUGVARIABLE_VARIABLE_DIMENSION:
		case N2_DEBUGVARIABLE_VARIABLE_ELEMENT:
			{
				n2_variable_t* var = (
					debugvar->type_ == N2_DEBUGVARIABLE_VARIABLE_DIMENSION ? debugvar->v_.var_dimension_.var_ : 
					debugvar->type_ == N2_DEBUGVARIABLE_VARIABLE_ELEMENT ? debugvar->v_.var_element_.var_ :
					debugvar->v_.var_root_
				);
				const int aptr = (
					debugvar->type_ == N2_DEBUGVARIABLE_VARIABLE_DIMENSION ? n2_variable_compute_aptr(var, debugvar->v_.var_dimension_.dimension_) : 
					debugvar->type_ == N2_DEBUGVARIABLE_VARIABLE_ELEMENT ? N2_SCAST(int, debugvar->v_.var_element_.element_index_ ):
					0
				);
				if (debugvar->type_ == N2_DEBUGVARIABLE_VARIABLE_ROOT)
				{
					n2_str_append_fmt(s, t, "\"name\": \"%s\"\n", var->name_);
				}
				else
				{
					n2_str_append_fmt(s, t, "\"name\": \"%s(", var->name_);
					size_t dim = 0;
					size_t length[N2_VARIABLE_DIM];
					N2_MEMSET(length, 0x00, sizeof(length));
					if (debugvar->type_ == N2_DEBUGVARIABLE_VARIABLE_DIMENSION)
					{
						for (size_t i = 0; i < N2_VARIABLE_DIM; ++i) { length[i] = debugvar->v_.var_dimension_.dimension_[i]; }
						dim = debugvar->v_.var_dimension_.dimension_index_ + 1;
					}
					else
					{
						n2_variable_compute_dimension_indices(length, aptr, var->length_);
						dim = n2_variable_compute_dimension_num(var->length_);
					}
					for (size_t i = 0; i < dim; ++i)
					{
						if (i > 0) { n2_str_append_fmt(s, t, ", "); }
						n2_str_append_fmt(s, t, "%zu", length[i]);
					}
					n2_str_append_fmt(s, t, ")\"\n");
				}
				n2_str_append_fmt(s, t, ", \"type\": \"%s\"\n", n2_valuetype_name(var->type_, "(unknown)"));
				n2_variable_inspect(s, state->environment_, &tvstr, var, aptr);
				n2_str_escaped_to(s, &tvestr, tvstr.str_, tvstr.size_, N2_STR_ESCAPE_FLAG_JSON);
				n2_str_append_fmt(s, t, ", \"value\": \"%s\"\n", tvestr.str_);
				n2_str_append_fmt(s, t, ", ");
				n2ri_dap_push_variables_reference(s, t, dap, state, debugvar);
			}
			break;
		case N2_DEBUGVARIABLE_FUNCTION_OARG:
		case N2_DEBUGVARIABLE_FUNCTION_KWARG:
			{
				const n2_bool_t is_keyworded_arg = debugvar->type_ == N2_DEBUGVARIABLE_FUNCTION_KWARG;

				n2_fiber_t* f = debugvar->v_.funcarg_.fiber_;
				const n2_func_t* func = NULL;
				int argbase = -1;
				if (debugvar->v_.funcarg_.callframe_index_ < 0)
				{
					func = f->callstate_.func_;
					argbase = f->callstate_.base_;
				}
				else
				{
					n2_callframe_t* cf = n2_callframearray_peek(f->callframes_, debugvar->v_.funcarg_.callframe_index_);
					func = cf ? cf->caller_function_ : NULL;
					argbase = cf ? cf->base_ : -1;
				}
				const n2_funcparamarray_t* funcparamarray = NULL;
				if (func) { funcparamarray = is_keyworded_arg ? func->keyworded_params_ : func->ordered_params_; }
				const int arg_index = debugvar->v_.funcarg_.arg_index_;
				const n2_func_param_t* funcparam = funcparamarray ? n2_funcparamarray_peekc(funcparamarray, arg_index) : NULL;
				if (func && argbase >= 0)
				{
					const n2_value_t* argvalue = n2_valuearray_peekv(f->values_, argbase + funcparam->stack_index_, NULL);
					if (argvalue)
					{
						n2_str_append_fmt(s, t, "\"name\": ");
						if (funcparam && funcparam->name_.str_) { n2_str_append_fmt(s, t, "\"%s\"", funcparam->name_.str_); }
						else { n2_str_append_fmt(s, t, "\"(%s%d)\"", is_keyworded_arg ? "kwarg" : "oarg", arg_index); }
						n2_str_append_fmt(s, t, "\n");
						n2_str_append_fmt(s, t, ", \"type\": \"%s\"\n", n2_valuetype_name(n2_value_get_type(argvalue), "(unknown)"));
						n2_value_inspect(s, state->environment_, &tvstr, argvalue);
						n2_str_escaped_to(s, &tvestr, tvstr.str_, tvstr.size_, N2_STR_ESCAPE_FLAG_JSON);
						n2_str_append_fmt(s, t, ", \"value\": \"%s\"\n", tvestr.str_);
						n2_str_append_fmt(s, t, ", ");
						if (argvalue->type_ == N2_VALUE_VARIABLE && argvalue->field_.varvalue_.var_->debugvarroot_)
						{
							n2ri_dap_push_variables_reference(s, t, dap, state, argvalue->field_.varvalue_.var_->debugvarroot_);
						}
						else
						{
							n2ri_dap_push_null_variables_reference(s, t, dap);
						}
					}
				}
			}
			break;
		default:
			break;
		}
		n2_str_teardown(s, &tvstr);
		n2_str_teardown(s, &tvestr);
	}
	n2_str_append_fmt(s, t, "}\n");
}

static void n2ri_dap_push_variable_filtered(n2_state_t* s, n2_str_t* t, n2r_dap_t* dap, n2_state_t* state, const n2_debugvariable_t* debugvar, const n2r_dap_varreq_param_t* varreq)
{
	int start = N2_MAX(0, varreq->start_);
	int left = varreq->count_;
	if (left <= 0) { left = INT32_MAX; }
	int pushed = 0;

#define N2RI_DAP_IMPL_TOPUSH() \
	if (start-- <= 0 && pushed < left)

#define N2RI_DAP_IMPL_PREPUSH() \
	do { \
		if (pushed > 0) { \
			n2_str_append_fmt(s, t, ", "); \
		} \
	} while (0)

#define N2RI_DAP_IMPL_POSTPUSH() \
	do { \
		++pushed; \
	} while (0)

	n2_str_append_fmt(s, t, "\"variables\": [\n");
	if (debugvar)
	{
		switch (debugvar->type_)
		{
		case N2_DEBUGVARIABLE_ENVIRONMENT:
			{
				n2_environment_t* e = debugvar->v_.environment_;
				if (varreq->include_named_)
				{
					const size_t named_num = n2_vartable_size_named(e->vartable_);
					for (size_t i = 0; i < named_num; ++i)
					{
						N2RI_DAP_IMPL_TOPUSH()
						{
							n2_variable_t* var = n2_vartable_peek_named(e->vartable_, N2_SCAST(int, i));
							if (var)
							{
								N2RI_DAP_IMPL_PREPUSH();
								n2ri_dap_push_variable_content(s, t, dap, state, var->debugvarroot_);
								N2RI_DAP_IMPL_POSTPUSH();
							}
						}
					}
				}
			}
			break;
		case N2_DEBUGVARIABLE_SYSVAR:
			{
				n2_fiber_t* f = debugvar->v_.sysvar_.fiber_;
				if (varreq->include_named_)
				{
					// 組み込み
					for (size_t i = 0; i < N2_MAX_SYSVAR; ++i)
					{
						N2RI_DAP_IMPL_TOPUSH()
						{
							n2_debugvariable_t* sysvardebugvar = f->debugvarsysvarelements_[i];
							if (sysvardebugvar)
							{
								N2RI_DAP_IMPL_PREPUSH();
								n2ri_dap_push_variable_content(s, t, dap, state, sysvardebugvar);
								N2RI_DAP_IMPL_POSTPUSH();
							}
						}
					}
					// 拡張
					for (size_t i = 0, l = n2_sysvarexarray_size(f->environment_->sysvar_ex_); i < l; ++i)
					{
						N2RI_DAP_IMPL_TOPUSH()
						{
							n2_sysvar_ex_t* sysvarex = n2_sysvarexarray_peek(f->environment_->sysvar_ex_, N2_SCAST(int, i));
							if (sysvarex && sysvarex->debugvarroot_)
							{
								N2RI_DAP_IMPL_PREPUSH();
								n2ri_dap_push_variable_content(s, t, dap, state, sysvarex->debugvarroot_);
								N2RI_DAP_IMPL_POSTPUSH();
							}
						}
					}
				}
			}
			break;
		case N2_DEBUGVARIABLE_FIBER:
		case N2_DEBUGVARIABLE_FIBER_CALLFRAME:
			{
				const n2_bool_t is_fiber = debugvar->type_ == N2_DEBUGVARIABLE_FIBER;
				n2_fiber_t* f = is_fiber ? debugvar->v_.fiber_ : debugvar->v_.fiber_cf_.fiber_;
				const n2_func_t* func = NULL;
				n2_debugvararray_t* funcargs = NULL;
				if (is_fiber)
				{
					func = f->callstate_.func_;
					funcargs = f->callstate_.debugvarargs_;
				}
				else
				{
					n2_callframe_t* cf = debugvar->v_.fiber_cf_.callframe_index_ >= 0 ? n2_callframearray_peek(f->callframes_, debugvar->v_.fiber_cf_.callframe_index_) : NULL;
					func = cf ? cf->caller_function_ : NULL;
					funcargs = cf ? cf->debugvarargs_ : NULL;
				}

				if (varreq->include_named_)
				{
					if (func && funcargs)
					{
						for (size_t i = 0, l = n2_debugvararray_size(funcargs); i < l; ++i)
						{
							N2RI_DAP_IMPL_TOPUSH()
							{
								n2_debugvariable_t* funcarg = n2_debugvararray_peekv(funcargs, N2_SCAST(int, i), NULL);
								if (funcarg)
								{
									N2RI_DAP_IMPL_PREPUSH();
									n2ri_dap_push_variable_content(s, t, dap, state, funcarg);
									N2RI_DAP_IMPL_POSTPUSH();
								}
							}
						}
					}
				}
			}
			break;
		case N2_DEBUGVARIABLE_FIBER_RELATIVES:
		case N2_DEBUGVARIABLE_FIBER_CALLFRAME_RELATIVES:
			{
				const n2_bool_t is_fiber = debugvar->type_ == N2_DEBUGVARIABLE_FIBER_RELATIVES;
				n2_fiber_t* f = is_fiber ? debugvar->v_.fiber_ : debugvar->v_.fiber_cf_.fiber_;
				const n2_intset_t* relatives = NULL;

				if (is_fiber)
				{
					n2_debugvarrelatives_update(state, f->environment_, &f->debugvarrelatives_, &f->debugvarrelpc_, f->op_pc_, dap->relative_variabls_line_range_);
					relatives = &f->debugvarrelatives_;
				}
				else
				{
					n2_callframe_t* cf = debugvar->v_.fiber_cf_.callframe_index_ >= 0 ? n2_callframearray_peek(f->callframes_, debugvar->v_.fiber_cf_.callframe_index_) : NULL;
					if (cf)
					{
						n2_debugvarrelatives_update(state, f->environment_, &cf->debugvarrelatives_, &cf->debugvarrelpc_, cf->caller_pc_, dap->relative_variabls_line_range_);
						relatives = &cf->debugvarrelatives_;
					}
				}

				if (varreq->include_named_)
				{
					if (relatives)
					{
						for (size_t i = 0, l = n2_intset_size(relatives); i < l; ++i)
						{
							N2RI_DAP_IMPL_TOPUSH()
							{
								const int* relvarindex = n2_intset_peekc(relatives, N2_SCAST(int, i));
								const n2_variable_t* relvar = relvarindex ? n2_vartable_peek(state->environment_->vartable_, *relvarindex) : NULL;
								if (relvar && relvar->debugvarroot_)
								{
									N2RI_DAP_IMPL_PREPUSH();
									n2ri_dap_push_variable_content(s, t, dap, state, relvar->debugvarroot_);
									N2RI_DAP_IMPL_POSTPUSH();
								}
							}
						}
					}
				}
			}
			break;
		case N2_DEBUGVARIABLE_VARIABLE_ROOT:
		case N2_DEBUGVARIABLE_VARIABLE_DIMENSION:
			{
				n2_variable_t* var = debugvar->type_ == N2_DEBUGVARIABLE_VARIABLE_ROOT ? debugvar->v_.var_root_ : debugvar->v_.var_dimension_.var_;
				if (varreq->include_indexed_)
				{
					const size_t dim = debugvar->type_ == N2_DEBUGVARIABLE_VARIABLE_ROOT ? 0 : debugvar->v_.var_dimension_.dimension_index_ + 1;
					if (dim < N2_VARIABLE_DIM - 1 && var->length_[dim + 1] > 0)
					{
						n2_variable_ensure_debugvariables(state, var, dim + 1);
						// まだ配列がある
						for (size_t i = 0; i < var->length_[dim]; ++i)
						{
							N2RI_DAP_IMPL_TOPUSH()
							{
								N2RI_DAP_IMPL_PREPUSH();
								n2ri_dap_push_variable_content(s, t, dap, state, n2_debugvararray_peekv(&var->debugvardims_[dim], N2_SCAST(int, i), NULL));
								N2RI_DAP_IMPL_POSTPUSH();
							}
						}
					}
					else
					{
						n2_variable_ensure_debugvariables(state, var, dim + 1);
						// 末端要素
						const int aptr_start = debugvar->type_ == N2_DEBUGVARIABLE_VARIABLE_ROOT ? 0 : n2_variable_compute_aptr_indim(var, debugvar->v_.var_dimension_.dimension_, dim + 1);
						const size_t element_num = var->length_[dim];
						for (size_t i = 0; i < element_num; ++i)
						{
							N2RI_DAP_IMPL_TOPUSH()
							{
								N2RI_DAP_IMPL_PREPUSH();
								n2ri_dap_push_variable_content(s, t, dap, state, n2_debugvararray_peekv(&var->debugvarelements_, aptr_start + N2_SCAST(int, i), NULL));
								N2RI_DAP_IMPL_POSTPUSH();
							}
						}
					}
				}
			}
			break;
		case N2_DEBUGVARIABLE_VARIABLE_ELEMENT:
			// no child
			break;
		default:
			break;
		}
	}
	n2_str_append_fmt(s, t, "]\n");

#undef N2RI_DAP_IMPL_TOPUSH
}

static void n2ri_dap_push_scopes(n2_state_t* s, n2_str_t* t, n2r_dap_t* dap, n2_state_t* state, n2_fiber_t* f, n2_callframe_t* cf, int cfindex)
{
	n2_str_append_fmt(s, t, "\"scopes\": [\n");
	// local scope
	{
		n2_str_append_fmt(s, t, "{\n");
		n2_str_append_fmt(s, t, "\"name\": \"Locals\"\n");
		n2_str_append_fmt(s, t, ", \"presentationHint\": \"locals\"\n");
		n2_str_append_fmt(s, t, ", \"expensive\": false\n");
		n2_pc_t use_pc = cf ? cf->caller_pc_ : f->op_pc_;
		int use_cfindex = cfindex;
		while (use_pc < 0 && dap->resolve_to_parent_callframe_on_external_)
		{
			++use_cfindex;
			const n2ri_dap_retrieve_callframe_t cfr = n2ri_dap_retrieve_callframe(state, f, use_cfindex);
			if (!cfr.is_valid_) { break; }
			use_pc = cfr.cf_ ? cfr.cf_->caller_pc_ : f->op_pc_;
		}
		const n2_codeline_t* codeline = use_pc >= 0 ? n2_codeimage_find_codeline_from_pc(f->environment_->codeimage_, use_pc) : NULL;
		if (codeline)
		{
			if (codeline->sourcecode_)
			{
				n2_str_append_fmt(s, t, ", \"source\": {\n");
				n2ri_dap_push_source_content(s, t, dap, state, codeline->sourcecode_);
				n2_str_append_fmt(s, t, "}\n");
			}
		}
		if (f->callstate_.func_ || f->callstate_.label_)
		{
			// @todo
			//const n2_sourcecode_t* sourcecode = f->callstate_.func_ ? f->callstate_.func_->source
			//n2_str_append_fmt(s, t, ", \"line\": %d\n", codeline->line_ + dap->line_base_);
			//n2_str_append_fmt(s, t, ", \"column\": %d\n", codeline->column_ + dap->line_base_);
			//n2_str_append_fmt(s, t, ", \"endLine\": 0\n");
			//n2_str_append_fmt(s, t, ", \"endColumn\": 0\n");
		}
		n2_debugvariable_t* debugvar = cf ? cf->debugvarroot_ : f->debugvarroot_;
		if (dap->enable_varref_ && debugvar)
		{
			n2_str_append_fmt(s, t, ", ");
			n2ri_dap_push_variables_reference(s, t, dap, state, debugvar);
		}
		n2_str_append_fmt(s, t, "}\n");
	}
	// relative variables scope
	if (dap->relative_variabls_line_range_ >= 0)
	{
		n2_str_append_fmt(s, t, ", {\n");
		n2_str_append_fmt(s, t, "\"name\": \"Relatives\"\n");
		n2_str_append_fmt(s, t, ", \"expensive\": false\n");
		n2_debugvariable_t* debugvar = cf ? cf->debugvarrelroot_ : f->debugvarrelroot_;
		if (dap->enable_varref_ && debugvar)
		{
			n2_str_append_fmt(s, t, ", ");
			n2ri_dap_push_variables_reference(s, t, dap, state, debugvar);
		}
		n2_str_append_fmt(s, t, "}\n");
	}
	// system variable scope
	{
		n2_str_append_fmt(s, t, ", {\n");
		n2_str_append_fmt(s, t, "\"name\": \"SysVars\"\n");
		n2_str_append_fmt(s, t, ", \"expensive\": false\n");
		if (dap->enable_varref_ && f->debugvarsysvar_)
		{
			n2_str_append_fmt(s, t, ", ");
			n2ri_dap_push_variables_reference(s, t, dap, state, f->debugvarsysvar_);
		}
		n2_str_append_fmt(s, t, "}\n");
	}
	// global scope
	{
		n2_str_append_fmt(s, t, ", {\n");
		n2_str_append_fmt(s, t, "\"name\": \"Globals\"\n");
		n2_str_append_fmt(s, t, ", \"expensive\": true\n");// 基本数が多いので高価に設定
		if (dap->enable_varref_ && f->environment_->debugvarroot_)
		{
			n2_str_append_fmt(s, t, ", ");
			n2ri_dap_push_variables_reference(s, t, dap, state, f->environment_->debugvarroot_);
		}
		n2_str_append_fmt(s, t, "}\n");
	}
	n2_str_append_fmt(s, t, "]\n");
}

static n2_bool_t n2r_dap_handle_scopes(n2r_dap_t* dap, int seq, const n2_str_t* commandstr, const n2h_datatree_t* argsnode)
{
	n2_state_t* es = dap->estate_;
	// 解析
	n2_str_t emessage; n2_str_init(&emessage);
	n2_bool_t res = N2_TRUE;
	if (dap->staging_state_)
	{
		n2_state_t* state = dap->staging_state_;

		const int frameid = N2_SCAST(int, n2h_datatree_asint(n2h_datatree_find_bystr(argsnode, "frameId"), -1));
		const int fiberid = N2RI_DAP_FIBERID_FROMFRAMEID(frameid);
		const int callframeindex = N2RI_DAP_CALLFRAMEINDEX_FROMFRAMEID(frameid);

		n2_fiber_t* f = n2_state_find_fiber(state, fiberid);
		const n2ri_dap_retrieve_callframe_t cfr = n2ri_dap_retrieve_callframe(state, f, callframeindex);

		if (cfr.is_valid_)
		{
			N2RI_DAP_TMESSAGE_BEGIN(dap);
			n2_str_append(s, t, "{\n", SIZE_MAX);
			{
				n2ri_dap_push_response_header(s, t, dap, seq, N2_TRUE, commandstr->str_, commandstr->size_, NULL);
				n2_str_append_fmt(s, t, ", \"body\": {\n");
				{
					n2ri_dap_push_scopes(s, t, dap, dap->staging_state_, f, cfr.cf_, callframeindex);
				}
				n2_str_append_fmt(s, t, "}\n");
			}
			n2_str_append(s, t, "}\n", SIZE_MAX);
			if (!n2ri_dap_push_message(dap, t->str_, t->size_)) { res = N2_FALSE; }
			N2RI_DAP_TMESSAGE_END(dap);
		}
		else
		{
			res = N2_FALSE;
			n2_str_fmt_to(es, &emessage, "No fiber(id=%d)&callframe(index=%d) corresponding to frameId(%d).", fiberid, callframeindex, frameid);
			if (!n2ri_dap_push_response_template(dap, seq, N2_FALSE, commandstr, emessage.str_)) { res = N2_FALSE; }
		}
	}
	else
	{
		res = N2_FALSE;
		n2_str_set(es, &emessage, "No staging state. Not launched yet", SIZE_MAX);
		if (!n2ri_dap_push_response_template(dap, seq, N2_FALSE, commandstr, emessage.str_)) { res = N2_FALSE; }
	}
	// 解放
	n2_str_teardown(es, &emessage);
	return res;
}

static n2_bool_t n2r_dap_handle_variables(n2r_dap_t* dap, int seq, const n2_str_t* commandstr, const n2h_datatree_t* argsnode)
{
	n2_state_t* es = dap->estate_;
	// 解析
	n2_str_t emessage; n2_str_init(&emessage);
	n2_bool_t res = N2_TRUE;
	if (dap->staging_state_)
	{
		n2_state_t* state = dap->staging_state_;

		const int varref = N2_SCAST(int, n2h_datatree_asint(n2h_datatree_find_bystr(argsnode, "variablesReference"), -1)) - dap->varref_base_;
		n2r_dap_varreq_param_t varreq_param;
		n2ri_dap_varreq_param_init(&varreq_param);
		const n2_str_t* filterstr = n2h_datatree_peekstr(n2h_datatree_find_bystr(argsnode, "filter"));
		varreq_param.start_ = N2_SCAST(int, n2h_datatree_asint(n2h_datatree_find_bystr(argsnode, "start"), 0));
		varreq_param.count_ = N2_SCAST(int, n2h_datatree_asint(n2h_datatree_find_bystr(argsnode, "count"), 0));
		if (filterstr && (n2ri_isstr(filterstr, "named") || n2ri_isstr(filterstr, "indexed")))
		{
			const n2_bool_t named = n2ri_isstr(filterstr, "named");
			varreq_param.include_named_ = named;
			varreq_param.include_indexed_ = !named;
		}

		const n2_debugvariable_t* debugvar = NULL;
		if (varref >= 0)
		{
			const size_t varrefsz = N2_SCAST(size_t, varref);
			const n2_debugvariable_t** p = n2_debugvarset_find(state->environment_->debugvarpool_->debugvars_, &varrefsz);
			if (p) { debugvar = *p; }
		}

		if (debugvar)
		{
			N2RI_DAP_TMESSAGE_BEGIN(dap);
			n2_str_append(s, t, "{\n", SIZE_MAX);
			{
				n2ri_dap_push_response_header(s, t, dap, seq, N2_TRUE, commandstr->str_, commandstr->size_, NULL);
				n2_str_append_fmt(s, t, ", \"body\": {\n");
				{
					n2ri_dap_push_variable_filtered(s, t, dap, dap->staging_state_, debugvar, &varreq_param);
				}
				n2_str_append_fmt(s, t, "}\n");
			}
			n2_str_append(s, t, "}\n", SIZE_MAX);
			if (!n2ri_dap_push_message(dap, t->str_, t->size_)) { res = N2_FALSE; }
			N2RI_DAP_TMESSAGE_END(dap);
		}
		else
		{
			res = N2_FALSE;
			n2_str_fmt_to(es, &emessage, "No variable found corresponding to variableReference(%d).", varref);
			if (!n2ri_dap_push_response_template(dap, seq, N2_FALSE, commandstr, emessage.str_)) { res = N2_FALSE; }
		}
	}
	else
	{
		res = N2_FALSE;
		n2_str_set(es, &emessage, "No staging state. Not launched yet", SIZE_MAX);
		if (!n2ri_dap_push_response_template(dap, seq, N2_FALSE, commandstr, emessage.str_)) { res = N2_FALSE; }
	}
	// 解放
	n2_str_teardown(es, &emessage);
	return res;
}

static n2_bool_t n2r_dap_handle_step(n2r_dap_t* dap, int seq, const n2_str_t* commandstr, const n2h_datatree_t* argsnode)
{
	n2_state_t* s = dap->estate_;
	dap->staging_continue_requested_ = N2_TRUE;
	int thread_id = -1;
	const n2_str_t* granularity = NULL;
	if (argsnode && n2h_datatree_type(argsnode) == N2H_DATATREE_MAP)
	{
		thread_id = N2_SCAST(int, n2h_datatree_asint(n2h_datatree_find_bystr(argsnode, "threadId"), -1));
		granularity = n2h_datatree_peekstr(n2h_datatree_find_bystr(argsnode, "granularity"));
	}
	// 解析
	n2_bool_t success = N2_TRUE;
	n2_str_t emessage; n2_str_init(&emessage);
	if (dap->staging_state_)
	{
		n2_state_t* state = dap->staging_state_;
		n2_fiber_t* f = n2_state_find_fiber(state, thread_id);
		if (f)
		{
			f->debugint_type_ = N2_DEBUGINT_NEXT;
			f->debugint_granularity_ = N2_DEBUGINT_GRANULARITY_STATEMENT;
			f->debugint_granule_size_ = 1;
			f->debugint_call_depth_ = 0;
			if (commandstr)
			{
				if (n2ri_isstr(commandstr, "pause")) { f->debugint_type_ = N2_DEBUGINT_PAUSE; f->debugint_granularity_ = N2_DEBUGINT_GRANULARITY_INSTRUCTION; }
				else if (n2ri_isstr(commandstr, "next")) { f->debugint_type_ = N2_DEBUGINT_NEXT; }
				else if (n2ri_isstr(commandstr, "stepIn")) { f->debugint_type_ = N2_DEBUGINT_STEPIN; }
				else if (n2ri_isstr(commandstr, "stepOut")) { f->debugint_type_ = N2_DEBUGINT_STEPOUT; }
			}
			if (granularity)
			{
				if (n2ri_isstr(granularity, "statement")) { f->debugint_granularity_ = N2_DEBUGINT_GRANULARITY_STATEMENT; }
				else if (n2ri_isstr(granularity, "line")) { f->debugint_granularity_ = N2_DEBUGINT_GRANULARITY_LINE; }
				else if (n2ri_isstr(granularity, "instrution")) { f->debugint_granularity_ = N2_DEBUGINT_GRANULARITY_INSTRUCTION; }
			}
		}
		else
		{
			success = N2_FALSE;
			n2_str_fmt_to(s, &emessage, "No thread corresponding to threadId(%d)", thread_id);
		}
	}
	else
	{
		success = N2_FALSE;
		n2_str_set(s, &emessage, "No staging state to next/stepIn/stepOut", SIZE_MAX);
	}
	// レスポンス
	n2_bool_t res = N2_TRUE;
	if (!n2ri_dap_push_response_template(dap, seq, success, commandstr, emessage.str_)) { res = N2_FALSE; }
	n2_str_teardown(s, &emessage);
	return res;
}

static n2_bool_t n2r_dap_handle_set_breakpoints(n2r_dap_t* dap, int seq, const n2_str_t* commandstr, const n2h_datatree_t* argsnode)
{
	n2_state_t* es = dap->estate_;
	// 解析
	n2_bool_t success = N2_TRUE;
	n2_str_t emessage; n2_str_init(&emessage);
	if (dap->staging_state_)
	{
		n2_state_t* state = dap->staging_state_;
		n2_codeimage_t* codeimage = state->environment_->codeimage_;

		const n2h_datatree_t* sourcenode = n2h_datatree_find_bystr(argsnode, "source");
		const n2h_datatree_t* breakpointsnode = n2h_datatree_find_bystr(argsnode, "breakpoints");
		//const n2_bool_t sourcemodified = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "sourceModified"), N2_FALSE);
		const n2_str_t* sourcefilepath = n2h_datatree_peekstr(n2h_datatree_find_bystr(sourcenode, "path"));
		const int sourcereference = N2_SCAST(int, n2h_datatree_asint(n2h_datatree_find_bystr(sourcenode, "sourceReference"), -1)) - dap->srcref_base_;

		// 該当するsourcefileを検索
		const n2_sourcefilearray_t* sourcefiles = codeimage->sourcefiles_;
		const n2_sourcefile_t* sourcefile = NULL;
		if (sourcefiles)
		{
			// sourceReferenceから一意に検索
			if (!sourcefile && sourcereference >= 0)
			{
				sourcefile = n2_sourcefilearray_peekcv(sourcefiles, sourcereference, NULL);
			}
			// pathから線形検索
			if (!sourcefile && sourcefilepath)
			{
				for (size_t i = 0, l = n2_sourcefilearray_size(sourcefiles); i < l; ++i)
				{
					const n2_sourcefile_t* psourcefile = *n2_sourcefilearray_peekc(sourcefiles, N2_SCAST(int, i));
					if (n2_path_compare(&psourcefile->src_resolved_filepath_, sourcefilepath) == 0)
					{
						sourcefile = psourcefile;
						break;
					}
				}
			}
		}
		if (breakpointsnode && n2h_datatree_type(breakpointsnode) == N2H_DATATREE_ARRAY)
		{
			// 全ブレイクポイントを張りなおす
			const size_t breakpointnum = n2h_datatree_arraysize(breakpointsnode);
			n2_intarray_t* breaklines = n2_intarray_alloc(es, breakpointnum, 16);
			n2_intset_t* sorted_breaklines = n2_intset_alloc(es, breakpointnum, 16);
			n2_intset_t* verified_breaklines = n2_intset_alloc(es, breakpointnum, 16);
			for (size_t i = 0; i < breakpointnum; ++i)
			{
				const n2h_datatree_t* breakpoint = n2h_datatree_at(breakpointsnode, N2_SCAST(int, i));
				const int64_t breakline = n2h_datatree_asint(n2h_datatree_find_bystr(breakpoint, "line"), -1);
				if (breakline >= 0)
				{
					const int ibreakline = N2_SCAST(int, breakline) - dap->line_base_;
					n2_intarray_pushv(es, breaklines, ibreakline);
					n2_intset_insert(es, sorted_breaklines, &ibreakline, NULL);
				}
			}

			n2_u8array_t* opcodeflags = codeimage->opcodeflags_;
			if (opcodeflags && sourcefile)// sourcefileが見つからないものは無視（全てUnverified）
			{
				for (size_t si = 0, sl = n2_sourcecodeptrarray_size(&sourcefile->sourcecodeptrs_); si < sl; ++si)
				{
					const n2_sourcecode_t* sourcecode = *n2_sourcecodeptrarray_peekc(&sourcefile->sourcecodeptrs_, N2_SCAST(int, si));
					for (size_t ci = 0, cl = n2_szarray_size(&sourcecode->codeline_indices_); ci < cl; ++ci)
					{
						const size_t codeline_index = *n2_szarray_peekc(&sourcecode->codeline_indices_, N2_SCAST(int, ci));
						const n2_codeline_t* codeline = n2_codelinetable_peekc(codeimage->codelinetable_, N2_SCAST(int, codeline_index));
						if (codeline)
						{
							uint8_t* opcode = n2_u8array_peek(opcodeflags, codeline->pc_);
							if (opcode)
							{
								const int line = N2_SCAST(int, codeline->line_);
								if (n2_intset_find(sorted_breaklines, &line))
								{
									n2_intset_insert(es, verified_breaklines, &line, NULL);
									*opcode |= N2_OPCODEFLAG_BREAKPOINT;
								}
								else
								{
									*opcode &= ~N2_OPCODEFLAG_BREAKPOINT;
								}
							}
						}
					}
				}

				// breakpointが正しく張れたか＝マッチしたコードがあったかだけで判定
				N2RI_DAP_TMESSAGE_BEGIN(dap);
				n2_str_append(s, t, "{\n", SIZE_MAX);
				{
					n2ri_dap_push_response_header(s, t, dap, seq, N2_TRUE, commandstr->str_, commandstr->size_, NULL);
					n2_str_append_fmt(s, t, ", \"body\": {\n");
					{
						n2_str_append_fmt(s, t, "\"breakpoints\": [\n");
						for (size_t i = 0; i < breakpointnum; ++i)
						{
							const int breakline = n2_intarray_peekv(breaklines, N2_SCAST(int, i), -1);
							const n2_bool_t verified = n2_intset_find(verified_breaklines, &breakline) ? N2_TRUE : N2_FALSE;
							if (i > 0) { n2_str_append_fmt(s, t, ", "); }
							n2_str_append_fmt(s, t, "{\n");
							n2_str_append_fmt(s, t, "\"verified\": %s\n", verified ? "true" : "false");
							//n2_str_append_fmt(s, t, ", \"id\": 0\n");
							//n2_str_append_fmt(s, t, ", \"message\": \"\"\n");
							n2_str_append_fmt(s, t, ", \"line\": %d\n", breakline + dap->line_base_);
							//n2_str_append_fmt(s, t, ", \"column\": 0\n");
							//n2_str_append_fmt(s, t, ", \"endLine\": 0\n");
							//n2_str_append_fmt(s, t, ", \"endColumn\": 0\n");
							//n2_str_append_fmt(s, t, ", \"instructionReference\": 0\n");
							//n2_str_append_fmt(s, t, ", \"offset\": 0\n");
							n2_str_append_fmt(s, t, "}\n");
						}
						n2_str_append_fmt(s, t, "]\n");
					}
					n2_str_append_fmt(s, t, "}\n");
				}
				n2_str_append(s, t, "}\n", SIZE_MAX);
				if (!n2ri_dap_push_message(dap, t->str_, t->size_)) { success = N2_FALSE; }
				N2RI_DAP_TMESSAGE_END(dap);
			}
			else
			{
				success = N2_FALSE;
				n2_str_fmt_to(es, &emessage, "Cannot set breakpoints (NoDebugMode).");
			}

			n2_intarray_free(es, breaklines);
			n2_intset_free(es, sorted_breaklines);
			n2_intset_free(es, verified_breaklines);
		}
		else
		{
			success = N2_FALSE;
			n2_str_fmt_to(es, &emessage, "Failed parsing arguments or source(%.*s) not found.", sourcefilepath ? sourcefilepath->size_ : 0, sourcefilepath ? sourcefilepath->str_ : "<unknown>");
		}
	}
	else
	{
		success = N2_FALSE;
		n2_str_set(es, &emessage, "No staging state to setBreakpoints.", SIZE_MAX);
	}
	// エラー時のレスポンス
	n2_bool_t res = N2_TRUE;
	if (!success && !n2ri_dap_push_response_template(dap, seq, success, commandstr, emessage.str_)) { res = N2_FALSE; }
	n2_str_teardown(es, &emessage);
	return res;

}

static n2_bool_t n2r_dap_handle(n2r_dap_t* dap, n2h_datatree_t* datatree)
{
	n2_state_t* s = dap->estate_;
	// タイプとシーケンスを取得
	const n2h_datatree_t* typenode = n2h_datatree_find_bystr(datatree, "type");
	if (!typenode || n2h_datatree_type(typenode) != N2H_DATATREE_STRING) { return N2_FALSE; }
	const n2_str_t* typestr = n2h_datatree_peekstr(typenode);
	N2_ASSERT(typestr);
	const int seq = N2_SCAST(int, n2h_datatree_asint(n2h_datatree_find_bystr(datatree, "seq"), -1));
	N2RI_DAP_LOGL(dap, "rcv message(%.*s) seq(%d)", N2_SCAST(int, typestr->size_), typestr->str_, seq);
	// タイプ別
	if (n2ri_isstr(typestr, "request"))
	{
		// コマンド
		const n2h_datatree_t* commandnode = n2h_datatree_find_bystr(datatree, "command");
		if (!commandnode || n2h_datatree_type(commandnode) != N2H_DATATREE_STRING) { return N2_FALSE; }
		const n2_str_t* commandstr = n2h_datatree_peekstr(commandnode);
		N2_ASSERT(commandstr);
		const n2h_datatree_t* argsnode = n2h_datatree_find_bystr(datatree, "arguments");
		N2RI_DAP_LOGL(dap, " request command(%.*s)", N2_SCAST(int, commandstr->size_), commandstr->str_);
		if (n2ri_isstr(commandstr, "initialize"))
		{
			// 初期化
			if (!argsnode || n2h_datatree_type(argsnode) != N2H_DATATREE_MAP) { return N2_FALSE; }
			// 内容の解析
			{
				dap->client_connected_ = N2_TRUE;

				n2ri_datatree_retrieve_str(s, &dap->client_id_, argsnode, "clientID");
				n2ri_datatree_retrieve_str(s, &dap->client_name_, argsnode, "clientName");
				n2ri_datatree_retrieve_str(s, &dap->client_adapter_id_, argsnode, "adapterID");
				n2ri_datatree_retrieve_str(s, &dap->client_locale_, argsnode, "locale");
				dap->client_line_start_at1_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "linesStartAt1"), N2_FALSE);
				dap->client_column_start_at1_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "columnsStartAt1"), N2_FALSE);
				n2ri_datatree_retrieve_str(s, &dap->client_path_format_, argsnode, "pathFormat");
				dap->client_support_variable_type_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "supportsVariableType"), N2_FALSE);
				dap->client_support_variable_paging_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "supportsVariablePaging"), N2_FALSE);
				dap->client_support_runinterminal_request_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "supportsRunInTerminalRequest"), N2_FALSE);
				dap->client_support_memory_reference_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "supportsMemoryReferences"), N2_FALSE);
				dap->client_support_progress_reporting_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "supportsProgressReporting"), N2_FALSE);
				dap->client_support_invalidated_event_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "supportsInvalidatedEvent"), N2_FALSE);

				dap->line_base_ = dap->client_line_start_at1_ ? 1 : 0;
				dap->column_base_ = dap->client_column_start_at1_ ? 1 : 0;
			}
			// レスポンス
			if (!n2ri_dap_push_response_initialize(dap, seq)) { return N2_FALSE; }
		}
		else if (n2ri_isstr(commandstr, "configurationDone"))
		{
			dap->staging_configuration_done_ = N2_TRUE;
			// レスポンス
			if (!n2ri_dap_push_response_template(dap, seq, N2_TRUE, commandstr, NULL)) { return N2_FALSE; }
		}
		else if (n2ri_isstr(commandstr, "launch"))
		{
			n2_bool_t success = N2_TRUE;
			n2r_dap_launch_param_t* launch_param = &dap->staging_state_launch_param_;
			n2ri_dap_launch_param_teardown(s, launch_param);
			n2ri_dap_launch_param_init(launch_param);
			n2_str_t emessage;
			n2_str_init(&emessage);
			if (argsnode && n2h_datatree_type(argsnode) == N2H_DATATREE_MAP)
			{
				const n2_str_t* program = n2h_datatree_peekstr(n2h_datatree_find_bystr(argsnode, "program"));
				if (program) { n2_str_copy_to(s, &launch_param->program_, program); }
				launch_param->no_debug_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "noDebug"), N2_FALSE);
				launch_param->stop_on_entry_ = n2h_datatree_asbool(n2h_datatree_find_bystr(argsnode, "stopOnEntry"), N2_FALSE);
				const n2_str_t* cwd = n2h_datatree_peekstr(n2h_datatree_find_bystr(argsnode, "cwd"));
				if (cwd) { n2_str_copy_to(s, &launch_param->cwd_, cwd); }
			}
			else
			{
				success = N2_FALSE;
			}
			// 先にcwdを決定する（カレントディレクトリを変更しておく）
			if (dap->staging_cwd_setfunc_ && 0)// 既に外側で処理されている想定なので、何もしない
			{
				n2_str_t cwd_dir;
				n2_str_init(&cwd_dir);
				if (launch_param->cwd_.size_ > 0)
				{
					n2_str_copy_to(s, &cwd_dir, &launch_param->cwd_);
				}
				else if (launch_param->program_.size_ > 0)
				{
					n2_path_split(s, &cwd_dir, NULL, NULL, &launch_param->program_);
				}
				// 決定できたら変える
				if (cwd_dir.size_ > 0)
				{
					dap->staging_cwd_setfunc_(dap, &cwd_dir);
				}
				n2_str_teardown(s, &cwd_dir);
			}
			// 付随するデータの読み込み
			n2_bool_t program_script_loaded = N2_FALSE;
			n2_str_t program_script;
			n2_str_init(&program_script);
			n2_str_t programstr_escaped;
			n2_str_init(&programstr_escaped);
			if (success)
			{
				if (launch_param->program_.size_ > 0)
				{
					n2_str_escaped_to(s, &programstr_escaped, launch_param->program_.str_, launch_param->program_.size_, N2_STR_ESCAPE_FLAG_JSON);
					program_script_loaded = n2_state_fs_load_str(s, &program_script, N2_STATE_FSFLAG_USE_SYSTEM_FS, launch_param->program_.str_, SIZE_MAX, 0);
				}
			}
			// 初期化
			if (dap->staging_state_)
			{
				// 既にあるのにまたlaunchしようとした
				success = N2_FALSE;
				n2_str_set(s, &emessage, "Try to launch without terminating previous launch session.", SIZE_MAX);
			}
			else if (!program_script_loaded)
			{
				success = N2_FALSE;
				n2_str_fmt_to(s, &emessage, "Failed opening program file(%s) to launch. No such file or cannot read.", programstr_escaped.str_);
			}
			else
			{
				// ステート作る
				n2_state_config_t sconfig;
				n2_state_config_init(&sconfig);

				if (launch_param->no_debug_)
				{
					//sconfig.generate_codelines_ = N2_FALSE;// 実行パフォーマンスに大きく影響はないのでそのまま
					sconfig.generate_debugvars_ = N2_FALSE;
				}
				else
				{
					sconfig.define_debug_ = N2_TRUE;
					sconfig.generate_opcodeflags_ = N2_TRUE;
					sconfig.generate_codelines_ = N2_TRUE;
					sconfig.generate_debugvars_ = N2_TRUE;// 変数のデバッグ表示
					sconfig.enable_graphics_assert_ = N2_TRUE;// 場合によってはそれなりのパフォーマンスオーバーヘッドになる
				}

				sconfig.print_log_ = n2ri_dap_print_log_func;
				sconfig.print_user_ = dap;

				if (dap->staging_state_setupfunc_)
				{
					dap->staging_state_setupfunc_(dap, &sconfig, launch_param);
				}

				n2_state_t* state = n2_state_alloc(&sconfig);
				if (state)
				{
					// デバッグフックの設定
					if (!launch_param->no_debug_)
					{
						n2_debughook_t* debughook = n2_environment_attach_debughook(state, state->environment_);
						if (debughook)
						{
							n2ri_dap_setup_debughook(dap, debughook);
						}
					}

					// 初期化
					n2_state_bind_basics(state);
					n2_state_bind_standards(state);

					if (dap->staging_state_preloadfunc_)
					{
						dap->staging_state_preloadfunc_(dap, state, launch_param);
					}

					if (n2_state_load_str(state, NULL, program_script.str_, program_script.size_, launch_param->program_.str_))
					{
						// デバッグ用
						//n2_codeimage_dump(state, state->environment_->codeimage_, state->environment_, N2_CODEIMAGE_DUMP_CODELINES);

						// 起動時にとまる
						if (launch_param->stop_on_entry_)
						{
							state->main_fiber_->debugint_type_ = N2_DEBUGINT_PAUSE;
							state->main_fiber_->debugint_granularity_ = N2_DEBUGINT_GRANULARITY_INSTRUCTION;
							state->main_fiber_->debugint_granule_size_ = 0;
						}

						// このステートで確定
						dap->staging_state_ = state;
						dap->staging_state_launched_by_dap_ = N2_TRUE;
					}
					else
					{
						// ロード失敗（このケースはDAP以前の問題なので、launch失敗とする）
						n2_state_free(state);
						success = N2_FALSE;
						n2_str_fmt_to(s, &emessage, "Failed loading program(%s). Use compile mode to detect errors.", programstr_escaped.str_);
					}
				}
				else
				{
					// ステート生成に失敗
					success = N2_FALSE;
					n2_str_set(s, &emessage, "Failed to create application instance.", SIZE_MAX);
				}
			}
			// レスポンス
			if (!n2ri_dap_push_response_template(dap, seq, success, commandstr, emessage.str_)) { return N2_FALSE; }
			n2_str_teardown(s, &programstr_escaped);
			n2_str_teardown(s, &program_script);
			n2_str_teardown(s, &emessage);
			if (!success) { return N2_FALSE; }
			// 正しくステートを生成できたら
			if (dap->staging_state_)
			{
				// configurationDone待ちに入る
				dap->staging_configuration_done_ = N2_FALSE;
				// initializedイベント
				if (!n2ri_dap_push_event_template(dap, "initialized", SIZE_MAX)) { return N2_FALSE; }
			}
			// 実際の実行は外側で行うので、ここでは何もしない
		}
		else if (n2ri_isstr(commandstr, "source"))
		{
			if (!n2r_dap_handle_source(dap, seq, commandstr, argsnode)) { return N2_FALSE; }
		}
		else if (n2ri_isstr(commandstr, "threads"))
		{
			if (!n2r_dap_handle_threads(dap, seq, commandstr)) { return N2_FALSE; }
		}
		else if (n2ri_isstr(commandstr, "stackTrace"))
		{
			if (!n2r_dap_handle_stack_trace(dap, seq, commandstr, argsnode)) { return N2_FALSE; }
		}
		else if (n2ri_isstr(commandstr, "scopes"))
		{
			if (!n2r_dap_handle_scopes(dap, seq, commandstr, argsnode)) { return N2_FALSE; }
		}
		else if (n2ri_isstr(commandstr, "variables"))
		{
			if (!n2r_dap_handle_variables(dap, seq, commandstr, argsnode)) { return N2_FALSE; }
		}
		//else if (n2ri_isstr(commandstr, "setVariable"))
		//{
		//}
		else if (n2ri_isstr(commandstr, "continue"))
		{
			dap->staging_continue_requested_ = N2_TRUE;
			// レスポンス
			if (!n2ri_dap_push_response_template(dap, seq, N2_TRUE, commandstr, NULL)) { return N2_FALSE; }
		}
		else if (n2ri_isstr(commandstr, "pause"))
		{
			if (!n2r_dap_handle_step(dap, seq, commandstr, argsnode)) { return N2_FALSE; }
		}
		else if (n2ri_isstr(commandstr, "next"))
		{
			if (!n2r_dap_handle_step(dap, seq, commandstr, argsnode)) { return N2_FALSE; }
		}
		else if (n2ri_isstr(commandstr, "stepIn"))
		{
			if (!n2r_dap_handle_step(dap, seq, commandstr, argsnode)) { return N2_FALSE; }
		}
		else if (n2ri_isstr(commandstr, "stepOut"))
		{
			if (!n2r_dap_handle_step(dap, seq, commandstr, argsnode)) { return N2_FALSE; }
		}
		//else if (n2ri_isstr(commandstr, "breakpointLocations"))
		//{
		//	if (!n2r_dap_handle_breakpoint_locations(dap, seq, commandstr, argsnode)) { return N2_FALSE; }
		//}
		else if (n2ri_isstr(commandstr, "setBreakpoints"))
		{
			if (!n2r_dap_handle_set_breakpoints(dap, seq, commandstr, argsnode)) { return N2_FALSE; }
		}
		else if (n2ri_isstr(commandstr, "terminate"))
		{
			// 強制的に破棄
			dap->staging_continue_requested_ = N2_TRUE;
			if (dap->staging_state_) { dap->staging_state_->main_fiber_->fiber_state_ = N2_FIBER_STATE_END; }
			// レスポンス
			if (!n2ri_dap_push_response_template(dap, seq, N2_TRUE, commandstr, NULL)) { return N2_FALSE; }
		}
		else if (n2ri_isstr(commandstr, "disconnect"))
		{
			// 接続扱い
			dap->client_connected_ = N2_FALSE;
			// disconnect時に自動的に閉じるか
			if (dap->close_when_dap_disconnected_)
			{
				dap->servertoclose_ = N2_TRUE;
				// dap生成のステージングは終了ステートに設定
				if (dap->staging_state_ && dap->staging_state_launched_by_dap_)
				{
					dap->staging_state_->main_fiber_->fiber_state_ = N2_FIBER_STATE_END;
				}
			}
			// レスポンス
			if (!n2ri_dap_push_response_template(dap, seq, N2_TRUE, commandstr, NULL)) { return N2_FALSE; }
		}
		else
		{
			// 分からん
			// レスポンス
			n2_str_t tstr;
			n2_str_init(&tstr);
			n2_str_fmt_to(s, &tstr, "Unhandled command(%.*s), NOT supprted.", commandstr->size_, commandstr->str_);
			n2ri_dap_push_response_template(dap, seq, N2_FALSE, commandstr, tstr.str_);
			n2_str_teardown(s, &tstr);
			return N2_FALSE;
		}
	}
	else if (n2ri_isstr(typestr, "event"))
	{
		// イベント
		const n2h_datatree_t* eventnode = n2h_datatree_find_bystr(datatree, "event");
		if (!eventnode || n2h_datatree_type(eventnode) != N2H_DATATREE_STRING) { return N2_FALSE; }
		const n2_str_t* eventstr = n2h_datatree_peekstr(eventnode);
		N2_ASSERT(eventstr);
		N2_UNUSE(eventstr);// @todo
		//const n2h_datatree_t* bodynode = n2h_datatree_find_bystr(datatree, "body");
	}
	else if (n2ri_isstr(typestr, "response"))
	{
		// リクエストシーケンスなど
		const n2h_datatree_t* reqseqnode = n2h_datatree_find_bystr(datatree, "request_seq");
		if (!reqseqnode || n2h_datatree_type(reqseqnode) != N2H_DATATREE_INT) { return N2_FALSE; }
		const n2h_datatree_t* successnode = n2h_datatree_find_bystr(datatree, "success");
		if (!successnode || n2h_datatree_type(successnode) != N2H_DATATREE_BOOL) { return N2_FALSE; }
		const n2h_datatree_t* commandnode = n2h_datatree_find_bystr(datatree, "command");
		if (!commandnode || n2h_datatree_type(commandnode) != N2H_DATATREE_STRING) { return N2_FALSE; }
		const n2_str_t* commandstr = n2h_datatree_peekstr(commandnode);
		N2_ASSERT(commandstr);
		N2_UNUSE(commandstr);// @todo
	}
	else
	{
		// 分からん
		return N2_FALSE;
	}
	return N2_TRUE;
}

static n2_bool_t n2r_dap_is_connected(n2r_dap_t* dap)
{
	return dap->remoteopen_ && !dap->remotetoclose_;
}

static n2_bool_t n2r_dap_updatable(n2r_dap_t* dap, n2_bool_t sleep)
{
	if (dap->serveropen_ && !dap->servertoclose_ && zed_net_check_connection_timeout(&dap->serversocket_, sleep ? dap->check_timeout_usec_ : 0) > 0) { return N2_TRUE; }
	if (dap->remoteopen_ && !dap->remotetoclose_ && zed_net_check_connection_timeout(&dap->remotesocket_, sleep ? dap->check_timeout_usec_ : 0) > 0) { return N2_TRUE; }
	return N2_FALSE;
}

static void n2r_dap_update_recv(n2r_dap_t* dap)
{
	// receive data if available
	while (dap->remoteopen_ && !dap->remotetoclose_)
	{
		const int c = zed_net_check_connection(&dap->remotesocket_);
		if (c < 0)
		{
			// illegal socket state
			dap->remotetoclose_ = N2_TRUE;
			break;
		}
		else if (c > 0)
		{
			int rcv_size = 0;
			n2_str_clear(&dap->rcvbuf_);// 必要ない気がするけど
			if (zed_net_tcp_socket_receive(&dap->remotesocket_, &rcv_size, dap->rcvbuf_.str_, N2_SCAST(int, dap->rcvbuf_.buffer_size_ * sizeof(char))))
			{
				dap->remotetoclose_ = N2_TRUE;
				break;
			}
			else
			{
				n2_str_append(dap->estate_, &dap->messagebuf_, dap->rcvbuf_.str_, N2_SCAST(size_t, rcv_size) / sizeof(char));
			}
		}
		else
		{
			// no data
			break;
		}
	}

	// handle received data
	while (dap->messagebuf_.size_ > 0)
	{
		if (dap->contentsize_ >= 0)
		{
			if (dap->messagebuf_.size_ >= N2_SCAST(size_t, dap->contentsize_))
			{
				N2RI_DAP_LOGL(dap, "rcv content ALL(%.*s)", N2_SCAST(int, dap->contentsize_), dap->messagebuf_.str_);
				// コンテンツを取得
				n2h_datatree_t* datatree = n2h_datatree_read_from_json(dap->estate_, dap->messagebuf_.str_, N2_SCAST(size_t, dap->contentsize_));
				if (datatree)
				{
					// ハンドル
					n2r_dap_handle(dap, datatree);
				}
				else
				{
					// パース失敗…
				}
				// 次のパケットへ
				n2_str_erase(&dap->messagebuf_, 0, N2_SCAST(size_t, dap->contentsize_));
				dap->contentsize_ = -1;
			}
			else
			{
				// まだコンテンツを取り切れてない
				break;
			}
		}
		else
		{
			// ヘッダとコンテントの境目
			const size_t twosep_size = N2_STRLEN(N2RI_DAP_TWOSEP);
			const int si = n2_str_find(&dap->messagebuf_, N2RI_DAP_TWOSEP, twosep_size, 0);
			if (si >= 0)
			{
				// ヘッダはここまで
				size_t hi = 0;
				const size_t sep_size = N2_STRLEN(N2RI_DAP_SEP);
				const size_t hs_size = N2_STRLEN(N2RI_DAP_HS);
				while (hi < N2_SCAST(size_t, si))
				{
					const int ni = n2_str_find(&dap->messagebuf_, N2RI_DAP_SEP, sep_size, hi);
					const int hsi = n2_str_find(&dap->messagebuf_, N2RI_DAP_HS, hs_size, hi);
					const int hv_size = ni - hsi - N2_SCAST(int, hs_size);
					if (hsi >= 0 && hv_size >= 0)
					{
						// ヘッダ解析
						const char* hh = dap->messagebuf_.str_ + hi;
						const char* hv = dap->messagebuf_.str_ + hsi + hs_size;
						if (N2_STRNCMP(hh, "Content-Length" ,N2_SCAST(size_t, hsi)) == 0)
						{
							// 雑解析
							dap->contentsize_ = N2_SCAST(int, N2_STRTOLL(hv, NULL, 0));
						}
						else
						{
							// 不明なヘッダー…
						}
					}
					else
					{
						// ヘッダセパレータがない…なら一旦無視
					}
					// 次へ
					hi = ni < 0 ? N2_SCAST(size_t, si/*やむを得ないのでもうヘッダ全部飛ばす*/) : (N2_SCAST(size_t, ni) + sep_size);
				}
				// あとはコンテンツ
				n2_str_erase(&dap->messagebuf_, 0, N2_SCAST(size_t, si + twosep_size));
			}
			else
			{
				// まだヘッダを取り切れてない
				break;
			}
		}
	}
}

static void n2r_dap_update_send(n2r_dap_t* dap)
{
	// response
	// tocloseだとしても、開かれているなら全部送る
	if (dap->responsebuf_.size_ > 0 && dap->remoteopen_)
	{
		if (zed_net_tcp_socket_send(&dap->remotesocket_, dap->responsebuf_.str_, N2_SCAST(int, dap->responsebuf_.size_ * sizeof(char))))
		{
			// 送信失敗
			dap->remotetoclose_ = N2_TRUE;
		}
		else
		{
			// 送信成功
		}
		n2_str_clear(&dap->responsebuf_);
	}
}

static void n2r_dap_update_connection(n2r_dap_t* dap)
{
	// check new accept
	if (!dap->remoteopen_)
	{
		if (dap->serveropen_ && !dap->servertoclose_)
		{
			const int c = zed_net_check_connection(&dap->serversocket_);
			if (c < 0)
			{
				dap->servertoclose_ = N2_TRUE;
			}
			else if (c > 0)
			{
				if (zed_net_tcp_accept(&dap->serversocket_, &dap->remotesocket_, &dap->remoteaddr_))
				{
					dap->servertoclose_ = N2_TRUE;
				}
				else
				{
					dap->remoteopen_ = N2_TRUE;
					++dap->accepted_count_;
					n2_str_clear(&dap->messagebuf_);
					n2_str_clear(&dap->responsebuf_);
				}
			}
		}
	}

	// to close ?
	if ((dap->remotetoclose_ || dap->servertoclose_) && dap->remoteopen_)
	{
		zed_net_socket_close(&dap->remotesocket_);
		dap->remoteopen_ = N2_FALSE;
		dap->remotetoclose_ = N2_FALSE;
		n2_str_clear(&dap->messagebuf_);
		n2_str_clear(&dap->responsebuf_);
		dap->client_connected_ = N2_FALSE;
	}
	if (dap->servertoclose_ && dap->serveropen_)
	{
		zed_net_socket_close(&dap->serversocket_);
		dap->serveropen_ = N2_FALSE;
		dap->servertoclose_ = N2_FALSE;
	}
}

static void n2ri_dap_poll_once(n2r_dap_t* dap)
{
	n2r_dap_update_connection(dap);
	n2r_dap_update_recv(dap);
	n2r_dap_update_send(dap);
}

static n2_bool_t n2ri_is_net_initialized = N2_FALSE;

static n2_bool_t n2ri_net_init()
{
	if (n2ri_is_net_initialized) { return N2_TRUE; }
	zed_net_init();
	n2ri_is_net_initialized = N2_TRUE;
	return N2_TRUE;
}

static n2_bool_t n2ri_net_teardown()
{
	if (!n2ri_is_net_initialized) { return N2_FALSE; }
	zed_net_shutdown();
	n2ri_is_net_initialized = N2_FALSE;
	return N2_TRUE;
}

static n2_bool_t n2r_dap_open(n2r_dap_t* dap, int port)
{
	if (dap->serveropen_) { return N2_FALSE; }
	n2ri_net_init();
	if (zed_net_tcp_socket_open(&dap->serversocket_, N2_SCAST(unsigned int, port), 0, 1)) { return N2_FALSE; }
	dap->serveropen_ = N2_TRUE;
	dap->servertoclose_ = N2_FALSE;
	return N2_TRUE;
}

static n2_bool_t n2r_dap_close(n2r_dap_t* dap)
{
	if (!dap->serveropen_) { return N2_TRUE; }
	dap->servertoclose_ = N2_TRUE;
	n2r_dap_update_connection(dap);
	if (dap->serveropen_) { return N2_FALSE; }
	n2ri_net_teardown();
	return N2_TRUE;
}

static n2_bool_t n2r_dap_reset_staging_state(n2r_dap_t* dap)
{
	if (dap->staging_state_)
	{
		// terminated
		n2ri_dap_push_event_template(dap, "terminated", SIZE_MAX);

		n2_state_free(dap->staging_state_);
		dap->staging_state_ = NULL;
	}
	dap->staging_state_launched_by_dap_ = N2_FALSE;
	return N2_TRUE;
}

static n2r_dap_t* n2r_dap_alloc(n2_state_t* estate)
{
	n2r_dap_t* dap = N2_TMALLOC(n2r_dap_t, estate);
	dap->estate_ = estate;
	dap->serveropen_ = N2_FALSE;
	dap->servertoclose_ = N2_FALSE;
	dap->remoteopen_ = N2_FALSE;
	dap->remotetoclose_ = N2_FALSE;
	dap->check_timeout_usec_ = 100;
	dap->accepted_count_ = 0;
	dap->enable_srcref_ = N2_FALSE;
	dap->enable_varref_ = N2_TRUE;
	dap->enable_dap_logging_ = N2_FALSE;
	dap->resolve_to_parent_callframe_on_external_ = N2_TRUE;
	dap->relative_variabls_line_range_ = 10;

	dap->close_when_dap_disconnected_ = N2_TRUE;

	n2_str_init(&dap->messagebuf_);
	n2_str_init(&dap->rcvbuf_);
	n2_str_reserve(estate, &dap->rcvbuf_, 1 * 1024 * 1024);
	dap->contentsize_ = -1;

	dap->send_sequence_id_ = 1;
	n2_str_init(&dap->responsebuf_);
	n2_str_reserve(estate, &dap->responsebuf_, 1 * 1024 * 1024);
	n2_str_set_expand_step(&dap->responsebuf_, 32 * 1024);

	dap->client_connected_ = N2_FALSE;
	n2_str_init(&dap->client_id_);
	n2_str_init(&dap->client_name_);
	n2_str_init(&dap->client_adapter_id_);
	n2_str_init(&dap->client_locale_);
	dap->client_line_start_at1_ = N2_FALSE;
	dap->client_column_start_at1_ = N2_FALSE;
	n2_str_init(&dap->client_path_format_);
	dap->client_support_variable_type_ = N2_FALSE;
	dap->client_support_variable_paging_ = N2_FALSE;
	dap->client_support_runinterminal_request_ = N2_FALSE;
	dap->client_support_memory_reference_ = N2_FALSE;
	dap->client_support_progress_reporting_ = N2_FALSE;
	dap->client_support_invalidated_event_ = N2_FALSE;

	dap->srcref_base_ = 1;
	dap->varref_base_ = 1;
	dap->line_base_ = 0;
	dap->column_base_ = 0;

	dap->staging_configuration_done_ = N2_FALSE;
	dap->staging_cwd_setfunc_ = NULL;
	dap->staging_state_setupfunc_ = NULL;
	dap->staging_state_preloadfunc_ = NULL;
	n2_str_init(&dap->staging_startupscript_path_);
	dap->staging_state_ = NULL;
	dap->staging_state_launched_by_dap_ = N2_FALSE;
	n2ri_dap_launch_param_init(&dap->staging_state_launch_param_);
	dap->staging_continue_requested_ = N2_FALSE;

	dap->user_ = NULL;
	return dap;
}

static void n2r_dap_free(n2r_dap_t* dap)
{
	n2_state_t* s = dap->estate_;

	n2r_dap_reset_staging_state(dap);
	n2r_dap_close(dap);

	n2ri_dap_launch_param_teardown(s, &dap->staging_state_launch_param_);
	n2_str_teardown(s, &dap->staging_startupscript_path_);

	n2_str_teardown(s, &dap->messagebuf_);
	n2_str_teardown(s, &dap->rcvbuf_);

	n2_str_teardown(s, &dap->responsebuf_);

	n2_str_teardown(s, &dap->client_id_);
	n2_str_teardown(s, &dap->client_name_);
	n2_str_teardown(s, &dap->client_adapter_id_);
	n2_str_teardown(s, &dap->client_locale_);
	n2_str_teardown(s, &dap->client_path_format_);

	n2_free(s, dap);
}

void n2ri_dap_debughook_pollfunc(n2_state_t* state, n2_debughook_t* dhook, size_t pollflags)
{
	N2_UNUSE(state);

	n2r_dap_t* dap = N2_RCAST(n2r_dap_t*, dhook->user_);
	if (!dap) { return; }

	do
	{
		n2ri_dap_poll_once(dap);
	}
	while (n2r_dap_updatable(dap, (pollflags & N2_DEBUGHOOK_POLLFLAG_BUSY) ? N2_FALSE : N2_TRUE));
}

void n2ri_dap_debughook_breakstopfunc(n2_state_t* state, n2_debughook_t* dhook, n2_fiber_t* fiber, n2_debughook_stop_reason_e reason)
{
	N2_UNUSE(state);

	n2r_dap_t* dap = N2_RCAST(n2r_dap_t*, dhook->user_);
	if (!dap) { return; }

	dap->staging_continue_requested_ = N2_FALSE;
	n2ri_dap_push_event_breakstopped(dap, fiber, reason, NULL);

	do
	{
		n2ri_dap_poll_once(dap);
		n2r_dap_updatable(dap, N2_TRUE);// sleep for busy loop
	}
	while (n2r_dap_is_connected(dap) && !dap->staging_continue_requested_/*break*/);
}

void n2ri_dap_debughook_errorstopfunc(n2_state_t* state, n2_debughook_t* dhook, const n2_error_param_t* error_param)
{
	N2_UNUSE(state);

	n2r_dap_t* dap = N2_RCAST(n2r_dap_t*, dhook->user_);
	if (!dap) { return; }

	dap->staging_continue_requested_ = N2_FALSE;
	n2ri_dap_push_event_breakstopped(dap, error_param->fiber_, N2_DEBUGHOOK_STOP_REASON_ERROR, error_param->raw_message_);

	do
	{
		n2ri_dap_poll_once(dap);
		n2r_dap_updatable(dap, N2_TRUE);// sleep for busy loop
	}
	while (n2r_dap_is_connected(dap) && !dap->staging_continue_requested_/*break*/);
}

void n2ri_dap_debughook_finfunc(n2_state_t* state, n2_debughook_t* dhook)
{
	N2_UNUSE(state);
	N2_UNUSE(dhook);
}

static void n2ri_dap_setup_debughook(n2r_dap_t* dap, n2_debughook_t* debughook)
{
	debughook->pollfunc_ = n2ri_dap_debughook_pollfunc;
	debughook->breakstopfunc_ = n2ri_dap_debughook_breakstopfunc;
	debughook->errorstopfunc_ = n2ri_dap_debughook_errorstopfunc;
	debughook->finfunc_ = n2ri_dap_debughook_finfunc;
	debughook->user_ = dap;
}

static void n2ri_dap_print_log_func(void* print_user, n2_state_t* state, n2_fiber_t* fiber, n2_log_level_e log_level, const char* str)
{
	N2_UNUSE(state);
	if (log_level != N2_LOG_LEVEL_LOGMES) { return; }
	const char* level =
		log_level == N2_LOG_LEVEL_LOGMES ? "console" : 
		log_level == N2_LOG_LEVEL_INFO ? "stdout" : 
		"stderr";
	if (!level) { return; }
	n2r_dap_t* dap = N2_RCAST(n2r_dap_t*, print_user);
	n2ri_dap_push_event_output(dap, str, fiber, level, NULL);
}

#endif // N2R_DAP_INCLUDED
