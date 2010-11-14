function getobjdir()
    return path.join(solution().basedir,
                     path.join("Build", path.join(_ACTION, project().name)))
end

function getdistdir()
    -- There is no way to get the current configuration until > premake 4.3.
    -- So just use the current action. Previously Dist/<first config> was
    -- always used for this, to ease running my test.sh script.
    return path.join(solution().basedir, path.join("Dist", _ACTION))
end

function getdepsdir()
    return path.join(solution().basedir, "Deps")
end

function make_Engine_templates()
    if not _ACTION then return end

    function make_call_templates()
        function commafiy(nargs, template)
            local s = ""

            for i = 1, nargs do
                s = s .. string.gsub(template, "[.]", i)
                if i < nargs then s = s .. ", " end
            end

            return s
        end

        local s = "/** convenience function for calling a scripts function" ..
                  " with the supplied arguments */\n"
        nargs = 8

        while nargs > 0 do
            s = s .. "        template <"
                  .. commafiy(nargs, "typename Arg._t")
                  .. "> void Call(const char *func, "
                  .. commafiy(nargs, "Arg._t arg.")
                  .. ")\n"
                  .. "        {\n"
                  .. "            PushFunction(func);\n"
            for i = 1, nargs do
                s = s .. "            Push(arg" .. i .. ");\n"
            end
            s = s .. "            Call();\n"
                  .. "        }\n"
            nargs = nargs - 1
        end
        return s
    end

    local fname = path.join(solution().basedir, "Include/Cassius/Engine.tpp")
    local relfname = path.getrelative(solution().basedir, fname)
    if _ACTION == "clean" then
        print("Removing " .. relfname)
        os.remove(fname)
    else
        print("Making " .. relfname)
        f = io.open(fname, "w+")
        f:write(make_call_templates(), "\n")
        f:close()
    end
end

