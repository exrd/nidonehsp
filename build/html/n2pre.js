
// already exists
//var Module = {};

Module.preRun.push(
	// bind n2r_ebin
	function() {
		var n2r_memfs_root = "/nidonehsp/res";
		FS.mkdirTree(n2r_memfs_root);
		//FS.mount(MEMFS, {}, n2r_memfs_root);

		FS.createPreloadedFile(n2r_memfs_root, "n2r_ebin", "./n2r_ebin", true, false);
	}
);

