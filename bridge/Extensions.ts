const fullbowody = require('../build/fullbowody.node');

class State {
    value: number;
    constructor(value: number) {
        this.value = value;
    }

    toString() {
        let val:string = "Unknown";
        switch (this.value) {
            case 0: val = "Error"; break;
            case 1: val = "Stopped"; break;
            case 2: val = "Started"; break;
            case 3: val = "Starting"; break;
            case 4: val = "Stopping"; break;
            default: break;
        }
        return val;
    }
}

class Extension {
    #name:string = "";
    #ip:string = "";
    #port:number = 0;

    constructor(data:any) {
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
        return new Promise((resolve, reject) => {
            fullbowody.extensions_start(resolve, reject);
        });
    }

    static stop() {
        return new Promise((resolve, reject) => {
            fullbowody.extensions_stop(resolve, reject);
        });
    }

    static getState() {
        return new State(fullbowody.extensions_getState());
    }

    static getInfos() {
        return {
            state: ExtensionsServer.getState().toString(),
            ip: fullbowody.extensions_getIp(),
            port: fullbowody.extensions_getPort()
        }
    }

    static onExtensionUpdate(callback:Function) {
        return fullbowody.extensions_onExtensionUpdate(callback);
    }

    static getExtensions() {
        const json = fullbowody.extensions_getExtensions();
        try {
            const obj = JSON.parse(json);
            if (!Array.isArray(obj)) return [];
            
            let exts:Extension[] = [];
            obj.forEach(ext => { exts.push(new Extension(ext)); });
            return exts;
        } catch { return [] }
    }
}

export default ExtensionsServer;