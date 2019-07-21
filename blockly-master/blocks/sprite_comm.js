'use strict';

goog.require('Blockly.Blocks');
goog.require('Blockly');

Blockly.defineBlocksWithJsonArray([
  {
    'type': 'send_uart',
    'message0': '%{BKY_SEND_UART} %1 %{BKY_SEND_UART_2} %2',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number'
    },
    {
      'type': 'input_value',
      'name': 'value',
    }],
    'style': 'math_blocks',
    'inputsInline': true
  },
  {
    'type': 'read_uart',
    'message0': '%{BKY_READ_UART} %1 %{BKY_READ_UART_2}',
    'args0': [{
      'type': 'input_value',
      'name': 'index',
      'check': 'Number'
    }],
    'output': 'Text',
    'style': 'math_blocks',
    'inputsInline': true
  },
])
