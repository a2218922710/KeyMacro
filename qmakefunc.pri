# 获取编译类型
defineReplace(SWQ_BUILD_TYPE) {
    CONFIG(debug, debug|release) {
        return (debug)
    } else {
        DEFINES += NDEBUG
        return (release)
    }
}

# 拷贝文件
defineReplace(SWQ_COPY_FILE) {
    SOURCE_OBJ = $$shell_path($$1)
    TARGET_OBJ = $$SWQ_MKDIR($$2)

    win32{
        system("copy $$SOURCE_OBJ $$TARGET_OBJ")
    } else {
        system("cp -vrfL $$SOURCE_OBJ $$TARGET_OBJ")
    }

    return ($$TARGET_OBJ)
}

# 创建文件路径
defineReplace(SWQ_MKDIR) {
    DIR = $$shell_path($$1)
    !exists($$DIR) {
        win32 {
            system("md $$DIR")
        } else {
            system("mkdir -p $$DIR")
        }
    }

    return ($$DIR)
}

# 删除目录
defineReplace(SWQ_RMDIR) {
    message("SWQ_RMDIR")
    DIR = $$shell_path($$1)
    exists($$DIR) {
        win32 {
            system("rmdir /s /q $$DIR")
        } else {
            system("rm -vfr $$DIR")
        }
    }
    return (SWQ_RMDIR)
}

defineReplace(SWQ_TOUCH) {
    file = $$1

    !exists($$file) {
        win32 {
            system("type nul>$$file")
        } else {
            system("touch $$file")
        }
    }
    return (SWQ_TOUCH)
}

defineReplace(SWQ_RMFILES) {
    message("SWQ_RMDIR")
    FILES = $$shell_path($$1)
    exists($$FILES) {
        win32 {
            system("del /Q $$FILES")
        } else {
            system("rm -vfr $$FILES")
        }
    }
    return (SWQ_RMDIR)
}

defineReplace(SWQ_COPY_DIR) {
    SOURCE_OBJ = $$shell_path($$1)
    TARGET_OBJ = $$SWQ_MKDIR($$2)

    win32{
        system("xcopy /E /Y $$SOURCE_OBJ $$TARGET_OBJ")
    } else {
        system("cp -vrfL $$SOURCE_OBJ/* $$TARGET_OBJ")
    }

    return ($$TARGET_OBJ)
}

defineReplace(SWQ_RUNLIBSUFFIX) {
    SUFFIX = so
    win32:SUFFIX = dll
    return ($$SUFFIX)
}

# 定义宏
defineReplace(SWQ_DEFINE) {
    key = $$1
    value = $$2
    message("SWQ_DEFINE: $$key")
    DEFINES += $${key}=\\\"$${value}\\\"
    return ($$DEFINES)
}

defineReplace(SWQ_COPY_QT_PLUGIN_EXCLUDING_DEBUG) {
    # 输入参数
    local_plugins_path = $$1
    target_plugins_path = $$2
    debug_dll_pattern = "d.dll"

    TEMP_DIR_WIN = $$system(echo %TEMP%)
    TEMP_DIR_WIN ~= s/\r?\n$//

    # 构建排除 debug 库的 xcopy 命令参数
    exclude_list_file = $$TEMP_DIR_WIN\qmake_copy_qt_plugin_excluding_debug.txt
    system("echo $${debug_dll_pattern} > $$exclude_list_file")

    exclude_pattern = $$shell_quote(/EXCLUDE:$${exclude_list_file})
    # 使用 xcopy 命令复制插件，同时排除 debug 库
    message("xcopy /E /I /Y /H $${local_plugins_path} $${target_plugins_path} $${exclude_pattern}")
    system("xcopy /E /I /Y /H $${local_plugins_path} $${target_plugins_path} $${exclude_pattern}")
    return ($$target_plugins_path)
}

# 安裝依赖
defineReplace(SWQ_INSTALL_QTLIB) {
    message("SWQ_INSTALL_QTLIB")

    INPUT = $$1
    OUT = $$2

    for(mod, QT) {
        win32{
            CONFIG(debug, debug|release) {
                QT_MOD = $${INPUT}/bin/Qt$${QT_MAJOR_VERSION}$${mod}d.dll
            } else {
                QT_MOD = $${INPUT}/bin/Qt$${QT_MAJOR_VERSION}$${mod}.dll
            }
            message(win:QT_MOD = $$QT_MOD)
            $$SWQ_COPY_FILE($$QT_MOD, $$OUT)
        } else {
            message(linux:QT_MOD = $$mod)
            !exists($$OUT) {
                system("mkdir -p $$OUT")
            }
            system("find $${INPUT} -iname libQt*$${mod}*.so.$${QT_MAJOR_VERSION} | \
                    xargs -I {} cp -vrfL {} $${OUT}")
        }

    }

    win32 {
        $$SWQ_COPY_QT_PLUGIN_EXCLUDING_DEBUG($$INPUT, $$OUT)
        $$SWQ_COPY_DIR($$INPUT/plugins, $$OUT/qt/plugins)
    } else {
        $$SWQ_COPY_DIR($$INPUT/plugins, $$OUT/qt/plugins)
        $$SWQ_COPY_FILE($$INPUT/lib/libQt5XcbQpa*.so.5, $$OUT)
        $$SWQ_COPY_FILE($$INPUT/lib/libQt5DBus*.so.5, $$OUT)
    }

    # 拷贝翻译文件
    QM_FILE_OUT = $$OUT/languages
    $$SWQ_MKDIR($$QM_FILE_OUT)
    $$SWQ_COPY_FILE($$INPUT/translations/qt_zh_CN.qm, $$QM_FILE_OUT)

    return (SWQ_INSTALL_QTLIB)
}

defineReplace(qmake_copy_qt_plugin) {
    in = $$to_local_path($$1)
    out = $$to_local_path($$2)
    win32 {
        $$SWQ_INSTALL_QTLIB($$in, $$out)
    } else {
        $$SWQ_COPY_FILE($$in, $$out)
    }

    return ($$out)
}

defineReplace(SWQ_INSTALL_CONANLIB) {
    INPUT = $$shell_path($$1/dependents/$$SPEC/$$SWQ_BUILD_TYPE()/lib)
    OUT = $$2
    $$SWQ_COPY_FILE($$INPUT/*.$$SWQ_RUNLIBSUFFIX(), $$OUT)

    $$SWQ_COPY_DIR($$INPUT/plugins, $$OUT/plugins)

    return (SWQ_INSTALL_CONANLIB)
}

defineReplace(SWQ_INSTALL_PROLIB) {
    message("SWQ_INSTALL_PROLIB")
    $$SWQ_COPY_FILE($$1, $$2)
    return (SWQ_INSTALL_PROLIB)
}

defineReplace(SWQ_PACKAGEINFO) {
    message("SWQ_PACKAGEINFO ...")
    outfile = $$1
    name = $$2
    version = $$3

    $$SWQ_RMFILES($$outfile)
    $$SWQ_TOUCH($$outfile)

    system("echo \[package\] >> $$outfile")
    system("echo name=$$name >> $$outfile")
    system("echo version=$$version >> $$outfile")
    message("SWQ_PACKAGEINFO end!")
    return (SWQ_PACKAGEINFO)
}

defineReplace(SWQ_LUPDATE) {
    win32{
        LOCAL_LUPDATE_BIN = $$(QTDIR)/bin/lupdate.exe
    } else {
        LOCAL_LUPDATE_BIN = $$(QTDIR)/bin/lupdate
    }
    return ($$LOCAL_LUPDATE_BIN)
}

defineReplace(SWQ_LLELEASE) {
    win32{
        LOCAL_LRELEASE_BIN =  $$(QTDIR)/bin/lrelease.exe
    } else {
        LOCAL_LRELEASE_BIN =  $$(QTDIR)/bin/lrelease
    }
    return ($$LOCAL_LRELEASE_BIN)
}
