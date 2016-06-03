
case 0:
for ( ; x < OP_SIZE_MAX; x++) {
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] == 0 && current_token == 0x0A) {
    output_assembled_opcode(opt_tmp, "d%d ", opt_tmp->hex);
    token_stack_pop_state(buffer_stack, 1);
    return SUCCEEDED;
  }
  if (opt_tmp->op[x] != toupper((int)current_token))
    break;

  token_stack_move(buffer_stack, 1);
}
break;

case 9:
case 1:
if (xbit_size > 8 && opt_tmp->skip_8bit == 1)
  break;
for ( ; x < OP_SIZE_MAX; x++) {
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] == 'x') {
    z = input_number();

    if (!(z == SUCCEEDED || z == INPUT_NUMBER_ADDRESS_LABEL || z == INPUT_NUMBER_STACK)) {
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }
    if (z == SUCCEEDED && (d > 255 || d < -128))
      break;
    if (operand_hint == HINT_16BIT)
      break;

    token_stack_push_state(buffer_stack);
    for (x++ ; x < OP_SIZE_MAX; x++) {
      current_token = token_stack_get_current_token(buffer_stack);
      if (opt_tmp->op[x] == 0 && current_token == 0x0A) {
        if (z == SUCCEEDED)
          output_assembled_opcode(opt_tmp, "d%d d%d ", opt_tmp->hex, d);
        else if (z == INPUT_NUMBER_ADDRESS_LABEL)
          output_assembled_opcode(opt_tmp, "k%d d%d R%s ", active_file_info_last->line_current, opt_tmp->hex, label);
        else {
          output_assembled_opcode(opt_tmp, "d%d c%d ", opt_tmp->hex, latest_stack);
          if (opt_tmp->type == 9) {
            /* 9 -> let's configure the stack so that all label references inside are relative */
            stacks_tmp->relative_references = 1;
          }
        }

        token_stack_pop_state(buffer_stack, 1);
        token_stack_pop_state(buffer_stack, 1);
        return SUCCEEDED;
      }
      if (opt_tmp->op[x] != toupper((int)current_token))
        break;

      token_stack_move(buffer_stack, 1);
    }
    token_stack_pop_state(buffer_stack, 0);
  }
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] != toupper((int)current_token))
    break;

  token_stack_move(buffer_stack, 1);
 }
break;

case 2:
for ( ; x < OP_SIZE_MAX; x++) {
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] == '?') {
    z = input_number();
    if (!(z == SUCCEEDED || z == INPUT_NUMBER_ADDRESS_LABEL || z == INPUT_NUMBER_STACK)) {
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }
    if (z == SUCCEEDED && (d > 65535 || d < -32768)) {
      print_error("Out of 16-bit range.\n", ERROR_NUM);
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }

    token_stack_push_state(buffer_stack);
    for (x++ ; x < OP_SIZE_MAX; x++) {
      current_token = token_stack_get_current_token(buffer_stack);
      if (opt_tmp->op[x] == 0 && current_token == 0x0A) {
        if (z == SUCCEEDED)
          output_assembled_opcode(opt_tmp, "d%d y%d ", opt_tmp->hex, d);
        else if (z == INPUT_NUMBER_ADDRESS_LABEL)
          output_assembled_opcode(opt_tmp, "k%d d%d r%s ", active_file_info_last->line_current, opt_tmp->hex, label);
        else
          output_assembled_opcode(opt_tmp, "d%d C%d ", opt_tmp->hex, latest_stack);

        token_stack_pop_state(buffer_stack, 1);
        token_stack_pop_state(buffer_stack, 1);
        return SUCCEEDED;
      }
      if (opt_tmp->op[x] != toupper((int)current_token))
        break;

      token_stack_move(buffer_stack, 1);
    }
    token_stack_pop_state(buffer_stack, 0);
  }
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] != toupper((int)current_token))
    break;

  token_stack_move(buffer_stack, 1);
}
break;

case 3:
for ( ; x < OP_SIZE_MAX; x++) {
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] == 0 && current_token == 0x0A) {
    output_assembled_opcode(opt_tmp, "y%d ", opt_tmp->hex);
    token_stack_pop_state(buffer_stack, 1);
    return SUCCEEDED;
  }
  if (opt_tmp->op[x] != toupper((int)current_token))
    break;

  token_stack_move(buffer_stack, 1);
}
break;

case 4:
s = 0;
for ( ; x < OP_SIZE_MAX; x++) {
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] == '?') {
    z = input_number();
    if (!(z == SUCCEEDED || z == INPUT_NUMBER_ADDRESS_LABEL || z == INPUT_NUMBER_STACK)) {
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }
    if (z == SUCCEEDED && (d > 65535 || d < -32768)) {
      print_error("Out of 16-bit range.\n", ERROR_NUM);
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }
    e = d;
    v = z;
    h = latest_stack;
    if (z == INPUT_NUMBER_ADDRESS_LABEL)
      strcpy(labelx, label);
    s = 1;
    break;
  }
  if (opt_tmp->op[x] != toupper((int)current_token))
    break;

  token_stack_move(buffer_stack, 1);
}
if (s == 0)
  break;

for (x++ ; x < OP_SIZE_MAX; x++) {
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] == '?') {
    z = input_number();
    if (!(z == SUCCEEDED || z == INPUT_NUMBER_ADDRESS_LABEL || z == INPUT_NUMBER_STACK)) {
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }
    if (z == SUCCEEDED && (d > 65535 || d < -32768)) {
      print_error("Out of 16-bit range.\n", ERROR_NUM);
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }
    r = d;
    t = z;
    u = latest_stack;
    if (z == INPUT_NUMBER_ADDRESS_LABEL)
      strcpy(labely, label);
    s = 2;
    break;
  }
  if (opt_tmp->op[x] != toupper((int)current_token))
    break;

  token_stack_move(buffer_stack, 1);
}
if (s == 1)
  break;

for (x++ ; x < OP_SIZE_MAX; x++) {
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] == '?') {
    z = input_number();
    if (!(z == SUCCEEDED || z == INPUT_NUMBER_ADDRESS_LABEL || z == INPUT_NUMBER_STACK)) {
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }
    if (z == SUCCEEDED && (d > 65535 || d < -32768)) {
      print_error("Out of 16-bit range.\n", ERROR_NUM);
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }
    s = 3;
    break;
  }
  if (opt_tmp->op[x] != toupper((int)current_token))
    break;

  token_stack_move(buffer_stack, 1);
}
if (s == 2)
  break;

for (x++ ; x < OP_SIZE_MAX; x++) {
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] == 0 && current_token == 0x0A) {

    output_assembled_opcode(opt_tmp, "d%d ", opt_tmp->hex);

    /* first operand */
    if (v == SUCCEEDED)
      output_assembled_opcode(opt_tmp, "y%d ", e);
    else if (v == INPUT_NUMBER_ADDRESS_LABEL)
      output_assembled_opcode(opt_tmp, "k%d r%s ", active_file_info_last->line_current, labelx);
    else
      output_assembled_opcode(opt_tmp, "C%d ", h);

    /* second operand */
    if (t == SUCCEEDED)
      output_assembled_opcode(opt_tmp, "y%d ", r);
    else if (t == INPUT_NUMBER_ADDRESS_LABEL)
      output_assembled_opcode(opt_tmp, "k%d r%s ", active_file_info_last->line_current, labely);
    else
      output_assembled_opcode(opt_tmp, "C%d ", u);

    /* third operand */
    if (z == SUCCEEDED)
      output_assembled_opcode(opt_tmp, "y%d ", d);
    else if (z == INPUT_NUMBER_ADDRESS_LABEL)
      output_assembled_opcode(opt_tmp, "k%d r%s ", active_file_info_last->line_current, label);
    else
      output_assembled_opcode(opt_tmp, "C%d ", latest_stack);
    
    token_stack_pop_state(buffer_stack, 1);
    return SUCCEEDED;
  }
  if (opt_tmp->op[x] != toupper((int)current_token))
    break;

  token_stack_move(buffer_stack, 1);
}
break;

case 5:
if (xbit_size > 8 && opt_tmp->skip_8bit == 1)
  break;
for ( ; x < OP_SIZE_MAX; x++) {
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] == 'x') {
    z = input_number();
    if (!(z == SUCCEEDED || z == INPUT_NUMBER_ADDRESS_LABEL || z == INPUT_NUMBER_STACK)) {
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }
    if (z == SUCCEEDED && (d > 255 || d < -128))
      break;

    e = d;
    v = z;
    h = latest_stack;
    if (z == INPUT_NUMBER_ADDRESS_LABEL)
      strcpy(labelx, label);
    
    token_stack_push_state(buffer_stack);
    for (x++; x < OP_SIZE_MAX; x++) {
      current_token = token_stack_get_current_token(buffer_stack);
      if (opt_tmp->op[x] == 'x') {
        z = input_number();
        if (!(z == SUCCEEDED || z == INPUT_NUMBER_ADDRESS_LABEL || z == INPUT_NUMBER_STACK)) {
          token_stack_pop_state(buffer_stack, 0);
          token_stack_pop_state(buffer_stack, 0);
          return FAILED;
        }
        if (z == SUCCEEDED && (d > 255 || d < -128))
          break;
        if (operand_hint == HINT_16BIT)
          break;
        
        token_stack_push_state(buffer_stack);
        for (x++; x < OP_SIZE_MAX; x++) {
          current_token = token_stack_get_current_token(buffer_stack);
          if (opt_tmp->op[x] == 0 && current_token == 0x0A) {
            if (v == SUCCEEDED)
              output_assembled_opcode(opt_tmp, "d%d d%d ", opt_tmp->hex, e);
            else if (v == INPUT_NUMBER_ADDRESS_LABEL)
              output_assembled_opcode(opt_tmp, "k%d d%d Q%s ", active_file_info_last->line_current, opt_tmp->hex, labelx);
            else
              output_assembled_opcode(opt_tmp, "d%d c%d ", opt_tmp->hex, h);
            
            if (z == SUCCEEDED)
              output_assembled_opcode(opt_tmp, "d%d ", d);
            else if (z == INPUT_NUMBER_ADDRESS_LABEL)
              output_assembled_opcode(opt_tmp, "k%d Q%s ", active_file_info_last->line_current, label);
            else
              output_assembled_opcode(opt_tmp, "c%d ", latest_stack);
            
            token_stack_pop_state(buffer_stack, 1);
            token_stack_pop_state(buffer_stack, 1);
            token_stack_pop_state(buffer_stack, 1);
            return SUCCEEDED;
          }
          if (opt_tmp->op[x] != toupper((int)current_token))
            break;

          token_stack_move(buffer_stack, 1);
        }
        token_stack_pop_state(buffer_stack, 0);
      }
      current_token = token_stack_get_current_token(buffer_stack);
      if (opt_tmp->op[x] != toupper((int)current_token))
        break;

      token_stack_move(buffer_stack, 1);
    }
    token_stack_pop_state(buffer_stack, 0);
  }
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] != toupper((int)current_token))
    break;

  token_stack_move(buffer_stack, 1);
}
break;

case 6:
for ( ; x < OP_SIZE_MAX; x++) {
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] == 'x') {
    z = input_number();
    if (!(z == SUCCEEDED || z == INPUT_NUMBER_ADDRESS_LABEL || z == INPUT_NUMBER_STACK)) {
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }
    if (z == SUCCEEDED && (d > 255 || d < -128))
      break;
    
    e = d;
    v = z;
    h = latest_stack;
    if (z == INPUT_NUMBER_ADDRESS_LABEL)
      strcpy(labelx, label);

    token_stack_push_state(buffer_stack);
    for (x++; x < OP_SIZE_MAX; x++) {
      current_token = token_stack_get_current_token(buffer_stack);
      if (opt_tmp->op[x] == '?') {
        z = input_number();
        if (!(z == SUCCEEDED || z == INPUT_NUMBER_ADDRESS_LABEL || z == INPUT_NUMBER_STACK)) {
          token_stack_pop_state(buffer_stack, 0);
          token_stack_pop_state(buffer_stack, 0);
          return FAILED;
        }
        if (z == SUCCEEDED && (d > 65535 || d < -32768)) {
          print_error("Out of 16-bit range.\n", ERROR_NUM);
          token_stack_pop_state(buffer_stack, 0);
          token_stack_pop_state(buffer_stack, 0);
          return FAILED;
        }

        token_stack_push_state(buffer_stack);
        for (x++; x < OP_SIZE_MAX; x++) {
          current_token = token_stack_get_current_token(buffer_stack);
          if (opt_tmp->op[x] == 0 && current_token == 0x0A) {
            
            if (v == SUCCEEDED)
              output_assembled_opcode(opt_tmp, "d%d d%d ", opt_tmp->hex, e);
            else if (v == INPUT_NUMBER_ADDRESS_LABEL)
              output_assembled_opcode(opt_tmp, "k%d d%d Q%s ", active_file_info_last->line_current, opt_tmp->hex, labelx);
            else
              output_assembled_opcode(opt_tmp, "d%d c%d ", opt_tmp->hex, h);
            
            if (z == SUCCEEDED)
              output_assembled_opcode(opt_tmp, "y%d ", d);
            else if (z == INPUT_NUMBER_ADDRESS_LABEL)
              output_assembled_opcode(opt_tmp, "k%d r%s ", active_file_info_last->line_current, label);
            else
              output_assembled_opcode(opt_tmp, "C%d ", latest_stack);
            
            token_stack_pop_state(buffer_stack, 1);
            token_stack_pop_state(buffer_stack, 1);
            token_stack_pop_state(buffer_stack, 1);
            return SUCCEEDED;
          }
          if (opt_tmp->op[x] != toupper((int)current_token))
            break;

          token_stack_move(buffer_stack, 1);
        }
        token_stack_pop_state(buffer_stack, 0);
      }
      current_token = token_stack_get_current_token(buffer_stack);
      if (opt_tmp->op[x] != toupper((int)current_token))
        break;

      token_stack_move(buffer_stack, 1);
    }
    token_stack_pop_state(buffer_stack, 0);
  }
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] != toupper((int)current_token))
    break;

  token_stack_move(buffer_stack, 1);
}
break;

case 7:
if (xbit_size > 8 && opt_tmp->skip_8bit == 1)
  break;
for ( ; x < OP_SIZE_MAX; x++) {
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] == 'x') {
    z = input_number();

    if (!(z == SUCCEEDED || z == INPUT_NUMBER_ADDRESS_LABEL || z == INPUT_NUMBER_STACK)) {
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }
    if (z == SUCCEEDED && (d > 255 || d < -128))
      break;
    if (operand_hint == HINT_16BIT)
      break;
    
    token_stack_push_state(buffer_stack);
    for (x++ ; x < OP_SIZE_MAX; x++) {
      current_token = token_stack_get_current_token(buffer_stack);
      if (opt_tmp->op[x] == 0 && current_token == 0x0A) {
        if (z == SUCCEEDED)
          output_assembled_opcode(opt_tmp, "d%d d%d ", opt_tmp->hex, d);
        else if (z == INPUT_NUMBER_ADDRESS_LABEL)
          output_assembled_opcode(opt_tmp, "k%d d%d Q%s ", active_file_info_last->line_current, opt_tmp->hex, label);
        else
          output_assembled_opcode(opt_tmp, "d%d c%d ", opt_tmp->hex, latest_stack);
        
        token_stack_pop_state(buffer_stack, 1);
        token_stack_pop_state(buffer_stack, 1);
        return SUCCEEDED;
      }
      if (opt_tmp->op[x] != toupper((int)current_token))
        break;

      token_stack_move(buffer_stack, 1);
    }
    token_stack_pop_state(buffer_stack, 0);
  }
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] != toupper((int)current_token))
    break;

  token_stack_move(buffer_stack, 1);
}
break;

case 8:
for ( ; x < OP_SIZE_MAX; x++) {
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] == 'x') {
    z = input_number();
    if (!(z == SUCCEEDED || z == INPUT_NUMBER_ADDRESS_LABEL || z == INPUT_NUMBER_STACK)) {
      token_stack_pop_state(buffer_stack, 0);
      return FAILED;
    }
    if (z == SUCCEEDED && (d > 255 || d < -128))
      break;

    e = d;
    v = z;
    h = latest_stack;
    if (z == INPUT_NUMBER_ADDRESS_LABEL)
      strcpy(labelx, label);

    token_stack_push_state(buffer_stack);
    for (x++; x < OP_SIZE_MAX; x++) {
      current_token = token_stack_get_current_token(buffer_stack);
      if (opt_tmp->op[x] == 'x') {
        z = input_number();
        if (!(z == SUCCEEDED || z == INPUT_NUMBER_ADDRESS_LABEL || z == INPUT_NUMBER_STACK)) {
          token_stack_pop_state(buffer_stack, 0);
          token_stack_pop_state(buffer_stack, 0);
          return FAILED;
        }
        if (z == SUCCEEDED && (d > 255 || d < -128))
          break;
        
        token_stack_push_state(buffer_stack);
        for (x++; x < OP_SIZE_MAX; x++) {
          current_token = token_stack_get_current_token(buffer_stack);
          if (opt_tmp->op[x] == 0 && current_token == 0x0A) {
            if (v == SUCCEEDED)
              output_assembled_opcode(opt_tmp, "d%d d%d ", opt_tmp->hex, e);
            else if (v == INPUT_NUMBER_ADDRESS_LABEL)
              output_assembled_opcode(opt_tmp, "k%d d%d Q%s ", active_file_info_last->line_current, opt_tmp->hex, labelx);
            else
              output_assembled_opcode(opt_tmp, "d%d c%d ", opt_tmp->hex, h);
            
            if (z == SUCCEEDED)
              output_assembled_opcode(opt_tmp, "d%d ", d);
            else if (z == INPUT_NUMBER_ADDRESS_LABEL)
              output_assembled_opcode(opt_tmp, "k%d R%s ", active_file_info_last->line_current, label);
            else {
              output_assembled_opcode(opt_tmp, "c%d ", latest_stack);
              /* let's configure the stack so that all label references inside are relative */
              stacks_tmp->relative_references = 1;
            }
            
            token_stack_pop_state(buffer_stack, 1);
            token_stack_pop_state(buffer_stack, 1);
            token_stack_pop_state(buffer_stack, 1);
            return SUCCEEDED;
          }
          if (opt_tmp->op[x] != toupper((int)current_token))
            break;

          token_stack_move(buffer_stack, 1);
        }
        token_stack_pop_state(buffer_stack, 0);
      }
      current_token = token_stack_get_current_token(buffer_stack);
      if (opt_tmp->op[x] != toupper((int)current_token))
        break;

      token_stack_move(buffer_stack, 1);
    }
    token_stack_pop_state(buffer_stack, 0);
  }
  current_token = token_stack_get_current_token(buffer_stack);
  if (opt_tmp->op[x] != toupper((int)current_token))
    break;

  token_stack_move(buffer_stack, 1);
}
break;
