LUPDATE_BIN = $$SWQ_LUPDATE()
LRELEASE_BIN = $$SWQ_LLELEASE()

# 生成qm文件
exists($$LRELEASE_BIN) {

message(LRELEASE_BIN = $$LRELEASE_BIN)

QM_FILE_OUT = $$SW_PROJECT_OUT/languages
$$SWQ_MKDIR($$QM_FILE_OUT)

system($$LRELEASE_BIN $$PWD/tr-zh_CN.ts -qm $$QM_FILE_OUT/tr-zh_CN.qm)

}