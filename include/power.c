powerset(char *original, int og_len, char *current, int curr_len)
{
    if (curr_len == og_len)
        if (numb_spaces(current) == g_optimal && balanced_valid(current, curr_len)))
            print(current);
        //do smthg

    if (!balanced_valid(current, curr_len))
        return;

    current[curr_len] = original[curr_len];
    powerset(original, og_len, current, curr_len+1);

    current[curr_len] = ' ';
    powerset(original, og_len, current, curr_len+1);

}
powerset_findnum(original, og_len, current, curr_len)
{
    if (curr_len == og_len)
        if (numb_spaces(current) < g_optimal && balanced_valid(current, curr_len)))
            numb_spaces(current) = g_optimal;
        //do smthg

    if (!balanced_valid(current, curr_len))
        return;

    current[curr_len] = original[curr_len];
    powerset(original, og_len, current, curr_len+1);

    current[curr_len] = ' ';
    powerset(original, og_len, current, curr_len+1);

}