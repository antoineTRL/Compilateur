typedef enum {
    AST_VOID,
    AST_INTEGER,
    AST_BINARY,
    AST_UNARY,
    AST_FUNCTION,
    AST_FNCALL,
    AST_VARIABLE,
    AST_CONDITION,
    AST_LOOP,
    AST_DECLARATION,
    AST_ASSIGNMENT,
    AST_COMPOUND_STATEMENT,
    AST_RETURN
} ast_node_type_e;

typedef enum {
    VAR_TYPE_INT,
    VAR_TYPE_VOID
} var_type_e;

typedef enum {
    AST_UNARY_NEGATE,
    AST_UNARY_NOT,
    AST_UNARY_INCREMENT,
    AST_UNARY_DECREMENT
} ast_unary_e;

typedef enum {
    AST_BINARY_ADD,
    AST_BINARY_SUBTRACT,
    AST_BINARY_MULTIPLY,
    AST_BINARY_DIVIDE,
    AST_BINARY_MODULO,
    AST_BINARY_AND,
    AST_BINARY_OR,
    AST_BINARY_EQ,  // Equal
    AST_BINARY_NEQ, // Not equal
    AST_BINARY_LT,  // Less than
    AST_BINARY_GT,  // Greater than
    AST_BINARY_LE,  // Less than or equal
    AST_BINARY_GE   // Greater than or equal
} ast_binary_e;

typedef struct ast_t {
    ast_node_type_e type;
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
            char op;
            struct ast_t *operand;
        } unary;
        struct {
            char *name;
            struct ast_list_t *args;
        } call;

        struct {
            char *name;
            var_type_e return_type;
            struct ast_list_t *params;
            struct ast_list_t *stmts;
        } function;
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
    };
} ast_t;