# shunting yard algo

```
for token in formula:
    if token is number:
        push to output queue.
    else if token is operator:
        while:
            token2 = get_top_of_operator_stack()
            if token2 not exist:
                break;
            if token2 is left parenthesis:
                break;
            if token2 has lower precedence than token:
                break;
            if token2 has equal precedence than token and token2 is not left associative:
                break;
            pop token2 from operator stack to output queue
        push token to operator stack
    else if token is left parenthesis:
        push token to operator stack
    else if token is right parenthesis:
        while:
            token2 = get_top_of_operator_stack()
            if token2 not exist:
                return error;
            if token2 is left parenthesis:
                only pop token2 from operator stack without send to output queue
                break;
            pop token2 from operator stack to output queue
while:
    token2 = get_top_of_operator_stack()
    if token2 is parethesis:
        return error;
    pop token2 from operator stack to output queue

exit ok

```
