/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include <inttypes.h>
#include <stddef.h>

#define MALLOC_SHMEM_LIBNAME "libmalloc_shmem.so"

typedef int64_t malloc_shmem_exported_address_space_handle_t;
typedef int64_t malloc_shmem_imported_address_space_handle_t;

typedef bool (*MallocShmemInitFT)();
#define MALLOC_SHMEM_INIT_FNAME "mallocShmemInit"

typedef void (*MallocShmemShutdownFT)();
#define MALLOC_SHMEM_SHUTDOWN_FNAME "mallocShmemShutdown"

typedef malloc_shmem_exported_address_space_handle_t (*MallocShmemExportWholeUserAddressSpaceFT)();
#define MALLOC_SHMEM_EXPORT_WHOLE_USER_ADDRESS_SPACE_FNAME "mallocShmemExportWholeUserAddressSpace"

typedef malloc_shmem_imported_address_space_handle_t (*MallocShmemImportAddressSpaceFT)(malloc_shmem_exported_address_space_handle_t src);
#define MALLOC_SHMEM_IMPORT_ADDRESS_SPACE_FNAME "mallocShmemImportAddressSpace"

typedef void (*MallocShmemReleaseImportedAddressSpaceFT)(malloc_shmem_imported_address_space_handle_t addressSpace);
#define MALLOC_SHMEM_RELEASE_IMPORTED_ADDRESS_SPACE_FNAME "mallocShmemReleaseImportedAddressSpace"

typedef void *(*MallocShmemMapImportedVaRangeFT)(malloc_shmem_imported_address_space_handle_t addressSpace, uintptr_t offset, size_t length);
#define MALLOC_SHMEM_MAP_IMPORTED_VA_RANGE_FNAME "mallocShmemMapImportedVaRange"

typedef void (*MallocShmemUnmapImportedVaRangeFT)(void *va);
#define MALLOC_SHMEM_RELEASE_IMPORTED_RANGE_FNAME "mallocShmemUnmapImportedVaRange"

typedef struct
{
    MallocShmemInitFT init;
    MallocShmemShutdownFT shutdown;
    MallocShmemExportWholeUserAddressSpaceFT exportWholeUserAddressSpace;
    MallocShmemImportAddressSpaceFT importAddressSpace;
    MallocShmemMapImportedVaRangeFT mapImportedVaRange;
    MallocShmemReleaseImportedAddressSpaceFT releaseImportedAddressSpace;
    MallocShmemUnmapImportedVaRangeFT unmapImportedVaRange;
} malloc_shmem_dispatch_table;

inline bool mallocShmemLoadDispatchTable(malloc_shmem_dispatch_table *dt, void *symLoaderPrivateData, void *(*symLoader)(void *symLoaderPrivateData, const char *symName)) {
    dt->init = (MallocShmemInitFT)symLoader(symLoaderPrivateData, MALLOC_SHMEM_INIT_FNAME);
    dt->shutdown = (MallocShmemShutdownFT)symLoader(symLoaderPrivateData, MALLOC_SHMEM_SHUTDOWN_FNAME);
    dt->exportWholeUserAddressSpace = (MallocShmemExportWholeUserAddressSpaceFT)symLoader(symLoaderPrivateData, MALLOC_SHMEM_EXPORT_WHOLE_USER_ADDRESS_SPACE_FNAME);
    dt->importAddressSpace = (MallocShmemImportAddressSpaceFT)symLoader(symLoaderPrivateData, MALLOC_SHMEM_IMPORT_ADDRESS_SPACE_FNAME);
    dt->releaseImportedAddressSpace = (MallocShmemReleaseImportedAddressSpaceFT)symLoader(symLoaderPrivateData, MALLOC_SHMEM_RELEASE_IMPORTED_ADDRESS_SPACE_FNAME);
    dt->mapImportedVaRange = (MallocShmemMapImportedVaRangeFT)symLoader(symLoaderPrivateData, MALLOC_SHMEM_MAP_IMPORTED_VA_RANGE_FNAME);
    dt->unmapImportedVaRange = (MallocShmemUnmapImportedVaRangeFT)symLoader(symLoaderPrivateData, MALLOC_SHMEM_RELEASE_IMPORTED_RANGE_FNAME);
    return dt->init && dt->shutdown && dt->exportWholeUserAddressSpace && dt->importAddressSpace && dt->mapImportedVaRange && dt->releaseImportedAddressSpace && dt->unmapImportedVaRange;
}
