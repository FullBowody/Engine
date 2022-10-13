const fullbowody = require('../build/fullbowody.node');

class State {
    value: number;
    constructor(value: number) {
        this.value = value;
    }

    toString() {
        let val:string;
        switch (this.value) {
            case 0: val = "Error"; break;
            case 1: val = "Stopped"; break;
            case 2: val = "Running"; break;
            default: val = "Unknown"; break;
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
            if (fullbowody.extensions_start()) resolve(undefined);
            else reject( fullbowody.extensions_getLastError() );
        });
    }

    static stop() {
        return new Promise((resolve, reject) => {
            if (fullbowody.extensions_stop()) resolve(undefined);
            else reject( fullbowody.extensions_getLastError() );
        });
    }

    static getState() {
        return new Promise((resolve, reject) => {
            resolve(new State(fullbowody.extensions_getState()));
        });
    }

    static getInfos() {
        return new Promise((resolve, reject) => {
            this.getState().then((state:any) => {
                resolve({
                    state: state.toString(),
                    ip: fullbowody.extensions_getIp(),
                    port: fullbowody.extensions_getPort()
                });
            }).catch(reject);
        });
    }

    static getExtensions() {
        return new Promise((resolve, reject) => {
            const json = fullbowody.extensions_getExtensions();
            try {
                const obj = JSON.parse(json);
                if (!Array.isArray(obj)) return [];
                
                let exts:Extension[] = [];
                obj.forEach(ext => { exts.push(new Extension(ext)); });
                resolve(exts);
            } catch { reject( fullbowody.extensions_getLastError() ); }
        })
    }
}

export default ExtensionsServer;