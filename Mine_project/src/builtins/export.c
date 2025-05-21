int ft_export(t_cmd *cmd, t_context *ctx)
{
    char *equal_sign;
    char *key;
    char *value;
    int status = 0;

    if (!cmd->args[1])
        return (ft_env(ctx));
    
    for (int i = 1; cmd->args[i]; i++)
    {
        equal_sign = ft_strchr(cmd->args[i], '=');
        if (equal_sign)
        {
            key = ft_strndup(cmd->args[i], equal_sign - cmd->args[i]);
            value = ft_strdup(equal_sign + 1);
            set_env_value(ctx, key, value);
            free(key);
            free(value);
        }
        else
        {
            // CORREÇÃO: Usar ctx->env em vez de *env
            if (!find_env_node(ctx->env, cmd->args[i]))
                set_env_value(ctx, ft_strdup(cmd->args[i]), NULL);
        }
    }
    return (status);
}