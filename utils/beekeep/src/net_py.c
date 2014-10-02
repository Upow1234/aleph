// thin python wrapper around net.h function calls
#include "Python.h"
#include "net.h"

// initialize the network 
static PyObject* /* void */ bees_init(/*void*/ PyObject* self, PyObject* args) {
  net_init();
  Py_RETURN_NONE;
}


// de-initialize the network 
static PyObject* /* void */ bees_deinit(/*void*/ PyObject* self, PyObject* args) {
  net_deinit();
  Py_RETURN_NONE;
}

// intialize (clear) an input node
static PyObject* /* void */ bees_init_inode(/* u16 idx */ PyObject* self, PyObject* args) {
  int a;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  net_init_inode((u16)a);
  Py_RETURN_NONE;
}

// intialize (clear) an output node
static PyObject* /* void */ bees_init_onode(/* u16 idx */ PyObject* self, PyObject* args) {
  int a;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  net_init_onode((u16)a);
  Py_RETURN_NONE;
}

// create a new operator given class ID, return index (-1 == fail)
static PyObject* /* s16 */ bees_add_op(/* op_id_t opId */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_add_op((op_id_t)a);
  return Py_BuildValue("i", b);
}

// remove the last created operator
static PyObject* /* s16 */ bees_pop_op(/* void */ PyObject* self, PyObject* args) {
  int a;
  a = net_pop_op();
  return Py_BuildValue("i", a);
}

// remove an arbitrary operator
// FIXME: not tested really... use at your own risk!
static PyObject* /* void */ bees_remove_op(/* const u32 idx */ PyObject* self, PyObject* args) {
  int a;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  net_remove_op(a);
  Py_RETURN_NONE;
}

/* // activate an input node with some input data */
/* static PyObject* /\* void *\/ bees_activate(/\* s16 inIdx, const io_t val, void* srcOp *\/ PyObject* self, PyObject* args) { */
/*   int a, b, c; */
/*   if (!PyArg_ParseTuple(args, "ii", &a, &b)) */
/*     return NULL; */
/*   net_activate(s16 inIdx, const io_t val, void* srcOp); */
/*   Py_RETURN_NONE; */
/* } */

// get current count of operators
static PyObject* /* u16 */ bees_num_ops(/* void */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "ii", &a, &b))
    return NULL;
  net_num_ops();
  return Py_BuildValue("i", a);
}

// get current count of inputs (including dsp parameters!)
static PyObject* /* u16 */ bees_num_ins(/* void */ PyObject* self, PyObject* args) {
  int a;
  a = net_num_ins();
  return Py_BuildValue("i", a);
}

// get current count of outputs
static PyObject* /* u16 */ bees_num_outs(/* void */ PyObject* self, PyObject* args) {
  int a;
  a = net_num_outs();
  return Py_BuildValue("i", a);
}

// get param index given index
static PyObject* /* s16 */ bees_param_idx(/* u16 inIdx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_param_idx(a);
  return Py_BuildValue("i", b);
}

// get num params (subset of inputs)
static PyObject* /* u16 */ bees_num_params(/* void */ PyObject* self, PyObject* args) {
  int a;
  a = net_num_params();
  return Py_BuildValue("i", a);
}

// get string for operator at given idx
static PyObject* /* const char* */ bees_op_name(/* const s16 idx */ PyObject* self, PyObject* args) {
  int a;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  return Py_BuildValue("s", net_op_name(a));
}

// get name for input at given idx
static PyObject* /* const char* */ bees_in_name(/* u16 idx */ PyObject* self, PyObject* args) {
  int a;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  return Py_BuildValue("s", net_in_name(a));
}

// get name for output at given idx
static PyObject* /* const char* */ bees_out_name(/* const u16 idx */ PyObject* self, PyObject* args) {
  int a;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  return Py_BuildValue("s", net_out_name(a));
}

// get op index for input at given idx
static PyObject* /* s16 */ bees_in_op_idx(/* const u16 idx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_in_op_idx(a);
  return Py_BuildValue("i", b);
}

// get op index for output at given idx
static PyObject* /* s16 */ bees_out_op_idx(/* const u16 idx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_out_op_idx(a);
  return Py_BuildValue("i", b);
}

// get global index for a given input of given op
//// NOTE: this is relatively slow, try not to use in realtime
static PyObject* /* u16 */ bees_op_in_idx(/* const u16 opIdx, const u16 inIdx */ PyObject* self, PyObject* args) {
  int a, b, c;
  if (!PyArg_ParseTuple(args, "ii", &a, &b))
    return NULL;
  c = net_op_in_idx(a, b);
  return Py_BuildValue("i", c);
}

// get global index for a given output of given op
static PyObject* /* u16 */ bees_op_out_idx(/* const u16 opIdx, const u16 outIdx */ PyObject* self, PyObject* args) {
  int a, b, c;
  if (!PyArg_ParseTuple(args, "ii", &a, &b))
    return NULL;
  c = net_op_out_idx(a, b);
  return Py_BuildValue("i", c);
}

// get connection index for output
static PyObject* /* s16 */ bees_get_target(/* u16 outIdx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_get_target(a);
  return Py_BuildValue("i", b);
}

// is this input connected to anything?
static PyObject* /* u8 */ bees_in_connected(/* s32 iIdx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_in_connected(a);
  return Py_BuildValue("i", b);
}

// get true/false for given op behavior flag
// (see op.h)
static PyObject* /* u8 */ bees_op_flag(/* const u16 opIdx, op_flag_t flag */ PyObject* self, PyObject* args) {
  int a, b, c;
  if (!PyArg_ParseTuple(args, "ii", &a, &b))
    return NULL;
  c = net_op_flag(a, b);
  return Py_BuildValue("i", c);
}

// get / set / increment input value
static PyObject* /* io_t */ bees_get_in_value(/* s32 inIdx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_get_in_value(a);
  return Py_BuildValue("i", b);
}

static PyObject* /* void */ bees_set_in_value(/* s32 inIdx, io_t val */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "ii", &a, &b))
    return NULL;
  net_set_in_value(a, b);
  Py_RETURN_NONE;
}

static PyObject* /* void */ bees_inc_in_value(/* s32 inIdx, io_t inc */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "ii", &a, &b))
      return NULL;
  net_inc_in_value(a, b);
  Py_RETURN_NONE;
}

// connect a given output and input idx pair
static PyObject* /* void */ bees_connect(/* u32 outIdx, u32 inIdx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "ii", &a, &b))
    return NULL;
  net_connect(a, b);
  Py_RETURN_NONE;
}

// disconnect a given output
static PyObject* /* void */ bees_disconnect(/* u32 outIdx */ PyObject* self, PyObject* args) {
  int a;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  net_disconnect(a);
  Py_RETURN_NONE;
}

// toggle preset inclusion for input
static PyObject* /* u8 */ bees_toggle_in_preset(/* u32 inIdx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_toggle_in_preset(a);
  return Py_BuildValue("i", b);
}

// toggle preset inclusion for output
static PyObject* /* u8 */ bees_toggle_out_preset(/* u32 outIdx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_toggle_out_preset(a);
  return Py_BuildValue("i", b);
}

// set preset inclusion for input
static PyObject* /* void */ bees_set_in_preset(/* u32 inIdx, u8 val */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "ii", &a, &b))
    return NULL;
  net_set_in_preset(a, b);
  Py_RETURN_NONE;
}

// set preset inclusion for output
static PyObject* /* void */ bees_set_out_preset(/* u32 outIdx, u8 val */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "ii", &a, &b))
    return NULL;
  net_set_out_preset(a, b);
  Py_RETURN_NONE;
}

// get preset inclusion for input
static PyObject* /* u8 */ bees_get_in_preset(/* u32 inIdx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_get_in_preset(a);
  return Py_BuildValue("i", b);
}

// get preset inclusion for output
static PyObject* /* u8 */ bees_get_out_preset(/* u32 outIdx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_get_out_preset(a);
  return Py_BuildValue("i", b);
}

// toggle play inclusion for input
static PyObject* /* u8 */ bees_toggle_in_play(/* u32 inIdx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_toggle_in_play(a);
  return Py_BuildValue("i", b);
}

// set play inclusion for input
static PyObject* /* void */ bees_set_in_play(/* u32 inIdx, u8 val */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "ii", &a, &b))
    return NULL;
  net_set_in_play(a, b);
  Py_RETURN_NONE;
}

// get play inclusion for input 
static PyObject* /* u8 */ bees_get_in_play(/* u32 inIdx */ PyObject* self, PyObject* args) {
  int a, b;
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  b = net_get_in_play(a);
  return Py_BuildValue("i", b);
}

// add a new parameter
/* static PyObject* /\* void *\/ bees_add_param(/\* u32 idx, const ParamDesc* pdesc *\/ PyObject* self, PyObject* args) { */
/*   int a, b; */
/*   if (!PyArg_ParseTuple(args, "ii", &a, &b)) */
/*     return NULL; */
/*   net_add_param(u32 idx, const ParamDesc* pdesc); */
/*   Py_RETURN_NONE; */
/* } */

// clear existing parameters
static PyObject* /* void */ bees_clear_params(/* void */ PyObject* self, PyObject* args) {
  net_clear_params();
  Py_RETURN_NONE;
}

// resend all parameter values
/* static PyObject* /\* void *\/ bees_send_params(/\* void *\/ PyObject* self, PyObject* args) { */
/*   int a, b; */
/*   if (!PyArg_ParseTuple(args, "ii", &a, &b)) */
/*     return NULL; */
/*   net_send_params(void); */
/*   Py_RETURN_NONE; */
/* } */

// get parameter string representations,
// given string buffer and index in inputs list
static PyObject* /* void */ bees_get_param_value_string(/* char* dst, u32 idx */ PyObject* self, PyObject* args) {
  int a;
  char str[32];
  if (!PyArg_ParseTuple(args, "i", &a))
    return NULL;
  net_get_param_value_string(str, a);
  return Py_BuildValue("s", str);
}

// same, with arbitrary value
static PyObject* /* void */ bees_get_param_value_string_conversion(/* char* dst, u32 idx, s32 val */ PyObject* self, PyObject* args) {
  int a, b;
  char str[32];
  if (!PyArg_ParseTuple(args, "ii", &a, &b))
    return NULL;
  net_get_param_value_string_conversion(str, a, b);
  Py_RETURN_NONE;
}


// retrigger all inputs
/* static PyObject* /\* void *\/ bees_retrigger_inputs(/\* void *\/ PyObject* self, PyObject* args) { */
/*   int a, b; */
/*   if (!PyArg_ParseTuple(args, "ii", &a, &b)) */
/*     return NULL; */
/*   net_retrigger_inputs(void); */
/*   Py_RETURN_NONE; */
/* } */

// populate an array with indices of all connected outputs for a given index
// returns count of connections
/* static PyObject* /\* u32 *\/ bees_gather(/\* s32 iIdx, u32(*outs)[NET_OUTS_MAX] *\/ PyObject* self, PyObject* args) { */
/*   int a, b; */
/*   if (!PyArg_ParseTuple(args, "ii", &a, &b)) */
/*     return NULL; */
/*   net_gather(s32 iIdx, u32(*outs)[NET_OUTS_MAX]); */
/*   Py_RETURN_NONE; */
/* } */

/* // query the blackfin for parameter list and populate pnodes */
/* /// this is now populated from offline descriptor file */
/* // static PyObject* /\* u8 *\/ bees_report_params(/\* void *\/ PyObject* self, PyObject* args) { */
/*   int a, b; */
/*   if (!PyArg_ParseTuple(args, "ii", &a, &b)) */
/*     return NULL; */
/* net_report_params(void); */
/*   Py_RETURN_NONE; */
/* } */

// pickle the network!
// return incremented pointer to dst
/* static PyObject* /\* u8* *\/ bees_pickle(/\* u8* dst *\/ PyObject* self, PyObject* args) { */
/*   int a, b; */
/*   if (!PyArg_ParseTuple(args, "ii", &a, &b)) */
/*     return NULL; */
/*   net_pickle(u8* dst); */
/*   Py_RETURN_NONE; */
/* } */

// unpickle the network!
// return incremented pointer to src
/* static PyObject* /\* u8* *\/ bees_unpickle(/\* const u8* src *\/ PyObject* self, PyObject* args) { */
/*   int a, b; */
/*   if (!PyArg_ParseTuple(args, "ii", &a, &b)) */
/*     return NULL; */
/*   net_unpickle(const u8* src); */
/*   Py_RETURN_NONE; */
/* } */

// clear ops and i/o
static PyObject* /* void */ bees_clear_user_ops(/* void */ PyObject* self, PyObject* args) {
  net_clear_user_ops();
  Py_RETURN_NONE;
}

// disconnect from parameters
static PyObject* /* void */ bees_disconnect_params(/* void */ PyObject* self, PyObject* args) {
  net_disconnect_params();
  Py_RETURN_NONE;
}

// insert a split after an output node
// return out11 of split if original out was unconnected,
// otherwise connect out1 of split to old target and return out2
/* static PyObject* /\* s16 *\/ bees_split_out(/\* s16 outIdx *\/ PyObject* self, PyObject* args) { */
/*   int a, b; */
/*   if (!PyArg_ParseTuple(args, "ii", &a, &b)) */
/*     return NULL; */
/*   net_split_out(s16 outIdx); */
/*   Py_RETURN_NONE; */
/* } */

/* /// test/dbg */
/* static PyObject* /\* void *\/ bees_print(/\* void *\/ PyObject* self, PyObject* args) { */
/*   int a, b; */
/*   if (!PyArg_ParseTuple(args, "ii", &a, &b)) */
/*     return NULL; */
/*   net_print(void); */
/*   Py_RETURN_NONE; */
/* } */
