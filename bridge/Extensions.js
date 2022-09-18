import fullbowody from "../build/Release/fullbowody";

class Extension {
    #name = "";
    #ip = "";
    #port = 0;

    constructor(data) {
        this.#name = data.name ?? "Unkwown name";
        this.#ip = data.ip ?? "XXX.XXX.XXX.XXX";
        this.#port = data.port ?? 0;
    }

    getName() { return this.#name }
    getPort() { return this.#port }
    getIp() { return this.#ip }
}

class ExtensionsServer {
    static start() {
        return fullbowody.extension_start();
    }

    static stop() {
        return fullbowody.extension_stop();
    }

    static getState() {
        return fullbowody.extension_getState();
    }

    static onExtensionUpdate(callback) {
        return fullbowody.extension_onExtensionUpdate(callback);
    }

    static getExtensions() {
        const json = fullbowody.extension_getExtensions();
        try {
            const obj = JSON.parse(json);
            if (!Array.isArray(obj)) return [];
            
            let exts = [];
            obj.forEach(ext => { exts.push(new Extension(ext)); });
            return exts;
        } catch { return [] }
    }
}

export default ExtensionsServer;