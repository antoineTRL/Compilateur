#ifndef AST_H
#define AST_H

typedef enum {
    AST_VOID,
    AST_INTEGER,
    AST_VARIABLE,
    AST_BINARY,
    AST_UNARY,
    AST_FUNCTION,
    AST_FNCALL,
    AST_COMPOUND_STATEMENT,
    AST_CONDITION,
    AST_LOOP,
    AST_RETURN,
    AST_ASSIGNMENT,
    AST_DECLARATION
} ast_type_e;

typedef enum {
    VAR_TYPE_VOID,
    VAR_TYPE_INT
} var_type_e;

typedef enum {
    AST_BINARY_ADD,
    AST_BINARY_SUBTRACT,
    AST_BINARY_MULTIPLY,
    AST_BINARY_DIVIDE
} ast_binary_e;

typedef enum {
    AST_UNARY_INCREMENT,
    AST_UNARY_DECREMENT
} ast_unary_e;

typedef struct ast_t {
    ast_type_e type;
    var_type_e var_type;
    union {
        long integer;
        struct {
            char *name;
            var_type_e type;
        } var;
        struct {
            ast_binary_e op;
            struct ast_t *left;
            struct ast_t *right;
        } binary;
        struct {
            ast_unary_e op;
            struct ast_t *operand;
        } unary;
        struct {
            char *name;
            var_type_e return_type;
            struct ast_list_t *params;
            struct ast_list_t *stmts;
        } function;
        struct {
            char *name;
            struct ast_list_t *args;
        } call;
        struct {
            struct ast_list_t *stmts;
        } compound_stmt;
        struct {
            struct ast_t *condition;
            struct ast_t *then;
            struct ast_t *Else;
        } condition;
        struct {
            struct ast_t *condition;
            struct ast_t *stmt;
        } loop;
        struct {
            struct ast_t *expr;
        } ret;
        struct {
            struct ast_t *lvalue;
            struct ast_t *rvalue;
        } assignment;
    };
} ast_t;

typedef struct ast_list_t {
    ast_t *elem;
    struct ast_list_t *next;
} ast_list_t;

ast_t *ast_new_variable(char *name, var_type_e type);
ast_t *ast_new_integer(long val);
ast_t *ast_new_binary(ast_binary_e op, ast_t *left, ast_t *right);
ast_t *ast_new_unary(ast_unary_e op, ast_t *operand);
ast_t *ast_new_function(char *name, var_type_e return_type, ast_list_t *params, ast_list_t *stmts);
ast_t *ast_new_fncall(char *name, ast_list_t *args);
ast_t *ast_new_comp_stmt(ast_list_t *stmts);
ast_t *ast_new_assignment(ast_t *lvalue, ast_t *rvalue);
ast_list_t *ast_list_new_node(ast_t *elem);
void ast_list_add(ast_list_t **list, ast_t *elem);
ast_t *ast_new_return(ast_t *expr);
ast_t *ast_new_loop(ast_t *condition, ast_t *stmt);
ast_t *ast_new_condition(ast_t *condition, ast_t *then, ast_t *Else);

#endif // AST_H
